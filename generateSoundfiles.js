const fs = require('fs');
const path = require('path');

// Audio-Ordner (relativ zum Skript)
const audioDir = path.join(__dirname, 'Audio');

// Arrays für Shader- und Set-Definitionen
const soundShaders = [];
const soundSets = [];

// Alle Audio-Dateien abrufen
const audioFiles = fs.readdirSync(audioDir).filter(file => {
    return file.endsWith('.ogg') || file.endsWith('.wav') || file.endsWith('.mp3');
});

// SoundShader- und SoundSet-Klassen generieren
audioFiles.forEach(file => {
    // Dateiname ohne Endung
    const baseName = path.basename(file, path.extname(file));

    // SoundShader-Klasse
    const soundShader = `
    class ${baseName}_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
    {
        samples[] = {{"AlbtrauminselAIVoice\\Audio\\${baseName}", 1}};
    };`;
    soundShaders.push(soundShader);

    // SoundSet-Klasse
    const soundSet = `
    class ${baseName}_SoundSet
    {
        soundShaders[] = {"${baseName}_SoundShader"};
    };`;
    soundSets.push(soundSet);
});

// Config-Datei als String zusammensetzen
const output = `
class CfgSoundShaders
{
    class AlbtrauminselAIVoice_SoundShaderBase
    {
        samples[] = {};
        frequency = 1;
        range = 25;
        volume = 0.8;
    };${soundShaders.join('\n')}
};

class CfgSoundSets
{${soundSets.join('\n')}
};
`;

// Ergebnis in eine Datei schreiben
fs.writeFileSync('generated_cfgsound.txt', output.trim(), 'utf-8');
console.log('✅ SoundShader- und SoundSet-Definitionen wurden in "generated_cfgsound.txt" geschrieben!');
