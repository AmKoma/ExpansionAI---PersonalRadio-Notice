modded class PersonalRadio
{
    const int RPC_RADIO_SOUND_PLAY = 3642541;

    ref EffectSound m_RadioSound;

    void TriggerBroadcastServer(string soundSet)
    {
        if (GetGame().IsClient())
            return;

        GetGame().RPCSingleParam(radio, RPC_RADIO_SOUND_PLAY, new Param1<string>(soundSet), true, null);
    }

    void PlayBroadcastClient(string soundSet)
    {
        if (!IsOperational())
        {
            return;
        }

        if (!GetGame().IsClient())
            return;

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
                PlayBroadcastClient(data.param1);
            }
        }
    }
}
