#include <stdio.h>
#include <stdlib.h>

int main() {
	for (int month = 1; month <= 12; ++month) {
		for (int day = 1; day <= 31; ++day) {
			char password[8 + 1] = {0};
			snprintf(password, sizeof(password), "%02d%02d1991", day, month);
			
			static const char FORMAT_STRING[] = "echo %8s| 7z-extra\\7za.exe t secret.7z 2>NUL 1>NUL";
			char command[sizeof(FORMAT_STRING) / sizeof(char) + sizeof(password) / sizeof(char) + 1] = {0};
			snprintf(command, sizeof(command), FORMAT_STRING, password);
			
			if (system(command) == 0) {
				printf("%s\n", password);
				return 0;
			}
		}
		printf("Tried month %02d.\n", month);
	}
	return 1;
}