modded class PersonalRadio
{
    const int RPC_RADIO_SOUND_PLAY = 3642541;
    const int RPC_RADIO_SOUND_STOP = 3642542;

    private const float COOLDOWN_TIME = 900.0;

    private float m_NextSoundTime = 0;
    ref EffectSound m_RadioSound;

    override void EEInit()
    {
        super.EEInit();
        if (GetGame().IsServer())
        {
            PersonalRadioTickManager.RegisterRadio(this);
        }
    }

    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);
        if (GetGame().IsServer())
        {
            PersonalRadioTickManager.UnregisterRadio(this);
        }
    }

    bool IsOperational()
    {
        return GetCompEM() && GetCompEM().IsWorking() && !IsRuined();
    }

    void CheckForEnemies()
    {
        float currentTime = GetGame().GetTime() / 1000.0;

        if (currentTime < m_NextSoundTime)
        {
            Print("[PersonalRadio] Cooldown active. Time left: " + (m_NextSoundTime - currentTime).ToString());
            return;
        }

        // 70% Chance
        if (Math.RandomFloat01() > 0.7)
        {
            Print("[PersonalRadio] RNG blockiert Funkspruch diese Runde.");
            return;
        }

        string factionName, locationName;
        if (DetectEnemyNearbyAndLocation(factionName, locationName))
        {
            Print("[PersonalRadio] Enemy detected! Faction: " + factionName + ", Location: " + locationName);
            PlayRadioPing(factionName, locationName);
            m_NextSoundTime = currentTime + COOLDOWN_TIME;
        }
        else
        {
            Print("[PersonalRadio] No valid enemy found or location unknown.");
        }
    }

    bool DetectEnemyNearbyAndLocation(out string outFaction, out string outLocation)
    {
        array<Object> nearby = new array<Object>();
        array<CargoBase> proxy = new array<CargoBase>();
        GetGame().GetObjectsAtPosition(GetPosition(), 750.0, nearby, proxy);

        foreach (Object obj : nearby)
        {
            eAIBase ai = eAIBase.Cast(obj);
            if (ai)
            {
                PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
                if (player && player.GetGroup() && ai.GetGroup() && player.GetGroup() == ai.GetGroup())
                    continue;

                if (!ai.GetGroup())
                    continue;

                eAIFaction faction = ai.GetGroup().GetFaction();
                if (!faction)
                    continue;

                string name = faction.GetName();
                if (!PersonalRadioTickManager.GetConfig().IsFactionAllowed(name))
                    continue;

                vector aiPos = ai.GetPosition();
                string location = GetLocationName(aiPos);

                if (location == "")
                    location = "Unknown";

                outFaction = name;
                outLocation = location;
                return true;
            }
        }

        return false;
    }

    void PlayRadioPing(string faction, string location)
    {
        location.Replace(" ", "_");
        string soundSet = string.Format("PersonalRadio_%1_%2_SoundSet", location, faction);
        Print("[PersonalRadio] Broadcasting sound: " + soundSet);

        GetGame().RPCSingleParam(this, RPC_RADIO_SOUND_PLAY, new Param1<string>(soundSet), true);
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (!GetGame().IsClient())
            return;

        if (rpc_type == RPC_RADIO_SOUND_PLAY)
        {
            Param1<string> data;
            if (ctx.Read(data))
            {
                PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
                if (!localPlayer)
                    return;

                float distance = vector.Distance(this.GetPosition(), localPlayer.GetPosition());
                if (distance > 50.0)
                    return;

                if (m_RadioSound)
                {
                    m_RadioSound.Stop();
                    m_RadioSound = null;
                }

                if (GetGame().ConfigIsExisting("CfgSoundSets " + data.param1))
                {
                    m_RadioSound = SEffectManager.PlaySoundOnObject(data.param1, this);
                }
                else
                {
                    m_RadioSound = SEffectManager.PlaySoundOnObject("PersonalRadio_Unknown_SoundSet", this);
                }
            }
        }

        if (rpc_type == RPC_RADIO_SOUND_STOP)
        {
            if (m_RadioSound)
            {
                m_RadioSound.Stop();
                m_RadioSound = null;
            }
        }
    }

    string GetLocationName(vector pos)
    {
        array<ref ExpansionLocation> locations = ExpansionLocation.GetWorldLocations();
        ExpansionLocation closest;
        float closestDistSq = int.MAX;
        vector pos2D = Vector(pos[0], 0, pos[2]);

        foreach (ExpansionLocation location : locations)
        {
            float distSq = vector.DistanceSq(pos2D, location.Position);
            if (distSq <= (location.Radius * location.Radius) && distSq < closestDistSq)
            {
                closest = location;
                closestDistSq = distSq;
            }
        }

        if (closest)
            return closest.Name;

        return "";
    }
}