modded class PersonalRadio
{
    const int RPC_RADIO_SOUND_PLAY = 3642541;
    const int RPC_RADIO_SOUND_STOP = 3642542;

    private const float COOLDOWN_TIME = 900.0;

    private float m_NextSoundTime = 0;
    private ref Timer m_CheckTimer;
    ref EffectSound m_RadioSound;

    override void EEInit()
    {
        super.EEInit();

        if (GetGame().IsServer())
        {
            m_CheckTimer = new Timer(CALL_CATEGORY_SYSTEM);
            m_CheckTimer.Run(5.0, this, "CheckForEnemies", null, true);
            Print("[PersonalRadio] Radio initialized, timer started.");
        }
    }

    void CheckForEnemies()
    {
        if (!GetCompEM() || !GetCompEM().IsWorking() || IsRuined())
        {
            Print("[PersonalRadio] Radio not working or is ruined.");

            // Sende Stop-Signal an Client, falls aktiv
            PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
            if (player)
            {
                GetGame().RPCSingleParam(this, RPC_RADIO_SOUND_STOP, null, true, player.GetIdentity());
            }
            return;
        }

        float currentTime = GetGame().GetTime() / 1000.0;

        if (currentTime < m_NextSoundTime)
        {
            Print("[PersonalRadio] Cooldown active. Time left: " + (m_NextSoundTime - currentTime).ToString());
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

        Print("[PersonalRadio] Nearby object count: " + nearby.Count());

        foreach (Object obj : nearby)
        {
            eAIBase ai = eAIBase.Cast(obj);
            if (ai)
            {
                Print("[PersonalRadio] Found eAI: " + ai.ToString());

                // Spieler ermitteln
                PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
                if (player && player.GetGroup() && ai.GetGroup())
                {
                    if (player.GetGroup() == ai.GetGroup())
                    {
                        Print("[PersonalRadio] -> eAI is in same group as player – ignoring.");
                        continue;
                    }
                }

                if (!ai.GetGroup())
                {
                    Print("[PersonalRadio] -> eAI has no group, skipping.");
                    continue;
                }

                eAIFaction faction = ai.GetGroup().GetFaction();
                if (!faction)
                {
                    Print("[PersonalRadio] -> eAI has no faction, skipping.");
                    continue;
                }

                string name = faction.GetName();
                Print("[PersonalRadio] -> eAI Faction: " + name);

                if (name == "Trader" || name == "Civilian")
                {
                    Print("[PersonalRadio] -> Skipping neutral/trader AI.");
                    continue;
                }

                vector aiPos = ai.GetPosition();
                string location = GetLocationName(aiPos);

                if (location == "")
                {
                    Print("[PersonalRadio] -> No location matched – using fallback.");
                    location = "Unknown";
                }

                Print("[PersonalRadio] Valid enemy found! Location: " + location + ", Faction: " + name);
                outFaction = name;
                outLocation = location;
                return true;
            }
        }

        return false;
    }

    void PlayRadioPing(string faction, string location)
    {
        // Ersetze Leerzeichen durch Unterstriche im Location-Namen
        location.Replace(" ", "_");

        string soundSet = string.Format("PersonalRadio_%1_%2_1_SoundSet", location, faction);
        Print("[PersonalRadio] Sending RPC to play sound: " + soundSet);

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
        if (player)
        {
            GetGame().RPCSingleParam(this, RPC_RADIO_SOUND_PLAY, new Param1<string>(soundSet), true, player.GetIdentity());
        }
    }

    override void OnWorkStop()
    {
        super.OnWorkStop();

        if (GetGame().IsServer())
        {
            PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
            if (player)
            {
                Print("[PersonalRadio] Radio turned off – sending STOP RPC.");
                GetGame().RPCSingleParam(this, RPC_RADIO_SOUND_STOP, null, true, player.GetIdentity());
            }
        }
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (GetGame().IsClient())
        {
            if (rpc_type == RPC_RADIO_SOUND_PLAY)
            {
                Param1<string> data;
                if (ctx.Read(data))
                {
                    Print("[PersonalRadio] Playing sound on client: " + data.param1);

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
                        Print("[PersonalRadio] SoundSet not found: " + data.param1 + " → Playing fallback.");
                        m_RadioSound = SEffectManager.PlaySoundOnObject("PersonalRadio_Unknown_SoundSet", this);
                    }
                }
            }

            if (rpc_type == RPC_RADIO_SOUND_STOP)
            {
                if (m_RadioSound)
                {
                    Print("[PersonalRadio] Stopping active sound on client.");
                    m_RadioSound.Stop();
                    m_RadioSound = null;
                }
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
        {
            string locName = closest.Name;
            Print("[PersonalRadio] -> Expansion location matched: " + locName);
            return locName;
        }

        Print("[PersonalRadio] -> No Expansion location match found.");
        return "";
    }
}
