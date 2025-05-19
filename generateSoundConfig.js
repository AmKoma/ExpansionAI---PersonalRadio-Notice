const fs = require('fs');
const path = require('path');

const AUDIO_DIR = path.join(__dirname, 'Audio');
const OUTPUT_FILE = path.join(__dirname, 'audio.cpp');

const AUDIO_EXTENSIONS = ['.ogg', '.wav'];

function getSoundEntries() {
    const files = fs.readdirSync(AUDIO_DIR);
    return files
        .filter(file => AUDIO_EXTENSIONS.includes(path.extname(file).toLowerCase()))
        .map(file => {
            const baseName = path.parse(file).name;
            return {
                name: baseName,
                path: `AlbtrauminselAIVoice\\Audio\\${baseName}`
            };
        });
}

function generateShaderBlock(entries) {
    const base = `
class CfgSoundShaders
{
    class AlbtrauminselAIVoice_SoundShaderBase
    {
        samples[] = {};
        frequency = 1;
        range = 25;
        volume = 0.8;
    };
`;
    const shaders = entries.map(entry => {
        return `    class ${entry.name}_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
    {
        samples[] = {{"${entry.path}", 1}};
    };`;
    }).join('\n\n');

    return base + shaders + '\n};';
}

function generateSetBlock(entries) {
    const sets = entries.map(entry => {
        return `    class ${entry.name}_SoundSet
    {
        soundShaders[] = {"${entry.name}_SoundShader"};
    };`;
    }).join('\n\n');

    return `\n\nclass CfgSoundSets\n{\n` + sets + '\n};';
}

function generateCpp() {
    const entries = getSoundEntries();
    const shaderBlock = generateShaderBlock(entries);
    const setBlock = generateSetBlock(entries);
    const fullContent = shaderBlock + setBlock;

    fs.writeFileSync(OUTPUT_FILE, fullContent);
    console.log(`✅ audio.cpp erfolgreich generiert mit ${entries.length} Einträgen.`);
}

generateCpp();
