class PersonalRadioConfigLoader
{
    static ref PersonalRadioConfig m_Config;

    static PersonalRadioConfig Get()
    {
        if (!m_Config)
        {
            m_Config = new PersonalRadioConfig();
            m_Config.Load();
        }

        return m_Config;
    }
}
