modded class PersonalRadio
{
    const int RPC_RADIO_SOUND_PLAY = 3642541;
    const int RPC_RADIO_SOUND_STOP = 3642542;

    ref EffectSound m_RadioSound;

    void TryPlayRemoteFunk(string soundSet)
    {
        if (!IsOperational())
        {
            Print("[PersonalRadio] Gerät nicht betriebsbereit – Funk abgelehnt.");
            return;
        }

        if (Math.RandomFloat01() > 0.7)
        {
            Print("[PersonalRadio] RNG < 0.7 – kein Funk.");
            return;
        }

        if (!GetGame().IsClient())
            return;

        Print("[PersonalRadio] Spiele SoundSet lokal: " + soundSet);

        if (m_RadioSound)
        {
            m_RadioSound.Stop();
            m_RadioSound = null;
        }

        if (GetGame().ConfigIsExisting("CfgSoundSets " + soundSet))
        {
            m_RadioSound = SEffectManager.PlaySoundOnObject(soundSet, this);
        }
        else
        {
            Print("[PersonalRadio] Fallback → spiele 'PersonalRadio_Unknown_SoundSet'");
            m_RadioSound = SEffectManager.PlaySoundOnObject("PersonalRadio_Unknown_SoundSet", this);
        }
    }

    bool IsOperational()
    {
        return GetCompEM() && GetCompEM().IsWorking() && !IsRuined();
    }

    override void OnWorkStop()
    {
        super.OnWorkStop();

        Print("[PersonalRadio] Gerät ausgeschaltet – Stoppe Sound.");

        if (GetGame().IsClient())
        {
            if (m_RadioSound)
            {
                m_RadioSound.Stop();
                m_RadioSound = null;
            }
        }
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
                Print("[PersonalRadio] RPC erhalten → Prüfe Gerät & spiele Sound: " + data.param1);

                // Sicherheitshalber nochmal prüfen
                if (IsOperational())
                {
                    TryPlayRemoteFunk(data.param1);
                }
                else
                {
                    Print("[PersonalRadio] Gerät nicht betriebsbereit bei RPC → kein Sound.");
                }
            }
        }

        if (rpc_type == RPC_RADIO_SOUND_STOP)
        {
            if (m_RadioSound)
            {
                Print("[PersonalRadio] STOP-RPC empfangen – Sound beenden.");
                m_RadioSound.Stop();
                m_RadioSound = null;
            }
        }
    }
}
