#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alsa/asoundlib.h>
#include <alsa/mixer.h>
#include <math.h>

int main(int argc, char const *argv[])
{
	char *split;
	char row[255];
	char battery[4];
	int intBattery;
	char batteryIcon[4];
	char batteryStatus[13];
	char batteryStatusIcon[4];
	FILE *fp;

	fp = fopen("/sys/class/power_supply/BAT0/uevent", "r");

	if (fp == NULL)
	{
		printf("Error");
	}

	while (fgets(row, sizeof(row), fp) != NULL)
	{
		if (strstr(row, "POWER_SUPPLY_CAPACITY=") != NULL)
		{
			split = strtok(row, "=");
			split = strtok(NULL, "=");
			strcpy(battery, split);
			intBattery = atoi(battery);
		}
		else if (strstr(row, "POWER_SUPPLY_STATUS") != NULL)
		{
			split = strtok(row, "=");
			split = strtok(NULL, "=");
			strcpy(batteryStatus, split);
		}
	}
	fclose(fp);

	long min, max;
	long volume;
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char *card = "default";
	const char *selem_name = "Master";
	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, selem_name);
	snd_mixer_elem_t *elem = snd_mixer_find_selem(handle, sid);

	snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_MONO, &volume);
	snd_mixer_selem_get_playback_volume_range(elem, &min, &max);

	float soundPercent = roundf((float)(long)volume / (float)max * 100.00);

	if (intBattery <= 20)
		strcpy(batteryIcon, "\0");

	if (intBattery <= 40)
		strcpy(batteryIcon, "\0");

	if (intBattery <= 60)
		strcpy(batteryIcon, "\0");

	if (intBattery <= 80)
		strcpy(batteryIcon, "\0");

	if (intBattery <= 100)
		strcpy(batteryIcon, "\0");

	if (strcmp(batteryStatus, "Discharging") == 0)
		strcpy(batteryStatusIcon, " \0");

	printf("%.0f 墳 %s%d %s\n", soundPercent, batteryStatusIcon, intBattery, batteryIcon);
}
