// Apply an attack or dampen effect to the given sound value based on the current time.
// The attack effect is applied when time < attackTime, and the dampen effect is applied when time > dampenTime.
// The sound value is multiplied by a factor ranging from 0 (silence) to 1 (original sound value).

float envelope(float time, float total_time, float attack, float dampen)
{
    if (time < attack) {
        // soundValue = soundValue * (i / (sampleRate * attack));
        // return value * attack;
        return time / attack;
        // value *= (i / (total_sound_samples * attack));
    } else if (time >= dampen) { 
        // Apply exponential dampen effect
        /*float dampen_factor = 1.0 - ((time - attack) / (dampen - attack));
        if (dampen_factor < 0)
        {
            dampen_factor = 0;
        }
        return value * pow(dampen_factor, 4);*/
        // float dampenFactor = (dampen - time) / (dampen - attack);
        // return value * ((dampen - time) / (dampen - attack));
        float time_since_dampen = time - dampen;
        //float dampen_factor = 1.0 - exp(-(time_since_dampen) / 0.1);
        //return value * dampen_factor;
        float dampen_factor = 1.0 - (time_since_dampen / (total_time - dampen));
        if (dampen_factor < 0)
        {
            dampen_factor = 0;
        }
        return pow(dampen_factor, 4);
    }
    return 1.0f;
}

/*float apply_envelope(float time, float soundValue, float attackTime, float dampenTime)
{
    if (time < attackTime) {
        // Apply attack effect
        return soundValue * (time / attackTime);
    } else if (time > dampenTime) {
        // Apply dampen effect
        return soundValue * ((dampenTime - time) / (dampenTime - attackTime));
    }
    // No effect
    return soundValue;
}*/

// else if (i >= 1 - sampleRate * decay)
// else // if (i >= total_sound_samples - total_sound_samples * decay)
/*float dampen = 0.0f;
if (instrumentType == 0)
{
    // dampen = pow(0.5f * log((frequency * volume) / sampleRate), 2.0f);
    dampen = pow(0.5f * log((frequency * volume) / total_sound_samples), 2.0f);
}
else if (instrumentType == 1)
{
    dampen = 1 + (frequency * 0.01f);
}
else if (instrumentType == 2)
{
    dampen = 1;
}
else
{
    dampen = pow(0.5f * log((frequency * volume) / total_sound_samples), 2.0f);
}*/
//value = value * pow((1.0f - ((i - (sampleRate * attack)) / (sampleRate * (sound_time_length - attack)))), dampen);
