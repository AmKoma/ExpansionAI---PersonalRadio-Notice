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
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(PersonalRadioTickManager.RunChecks, 60000, true);
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
        }
    }

    static void RunChecks()
    {
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