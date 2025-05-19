class PersonalRadioTickManager
{
    static ref array<PersonalRadio> m_Radios = new array<PersonalRadio>();
    static ref Timer m_GlobalTimer;
    static ref PersonalRadioConfig m_Config;

    static void Init()
    {
        if (!m_Config)
        {
            m_Config = new PersonalRadioConfig();
            m_Config.Load();
            Print("[PRTickManager] Config geladen.");
        }
    }

    static void RegisterRadio(PersonalRadio radio)
    {
        if (!m_Config)
            Init();

        if (m_Radios.Find(radio) == -1)
        {
            m_Radios.Insert(radio);

            if (!m_GlobalTimer)
            {
                m_GlobalTimer = new Timer(CALL_CATEGORY_SYSTEM);
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(PersonalRadioTickManager.RunChecks, 60000, true); // alle 60s, nach 5s Start
                Print("[PRTickManager] Timer gestartet.");
            }
        }
    }

    static void UnregisterRadio(PersonalRadio radio)
    {
        m_Radios.RemoveItem(radio);

        if (m_Radios.Count() == 0 && m_GlobalTimer)
        {
            m_GlobalTimer.Stop();
            m_GlobalTimer = null;
            Print("[PRTickManager] Timer gestoppt (keine Radios mehr registriert).\n");
        }
    }

    static void RunChecks()
    {
        Print("[PRTickManager] Globaler Tick: " + m_Radios.Count() + " Radios prüfen");
        foreach (PersonalRadio radio : m_Radios)
        {
            if (radio && radio.IsOperational())
            {
                radio.CheckForEnemies();
            }
        }
    }

    static PersonalRadioConfig GetConfig()
    {
        return m_Config;
    }
}