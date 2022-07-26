#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		strcpy(batteryStatusIcon, "\0");

	printf("%s %d %s\n", batteryStatusIcon, intBattery, batteryIcon);
}
