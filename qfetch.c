#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>

#define BLUE   "\033[1;34m"
#define RESET  "\033[0m"

const char *arch[] = {
    "      /\\        ",
    "     /  \\       ",
    "    /\\   \\      ",
    "   /      \\     ",
    "  /   ,,   \\    ",
    " /   |  |  -\\   ",
    "/_-''    ''-_\\  "
};

const char *arco[] = {
  "      /\\        ",
  "     /  \\       ",
  "    / /\\ \\      ",
  "   / /  \\ \\     ",
  "  / /    \\ \\    ",
  " / / _____\\ \\   ",
  "/_/  `----.\\_\\  "
};

const char *artix[] = {
  "      /\\        ",
  "     /  \\       ",
  "    /`'.,\\      ",
  "   /     '\\     ",
  "  /      ,`\\    ",
  " /   ,.'`.  \\   ",
  "/.,'`     `'`\\  "
};

const char *debian[] = {
  "  _____         ",
  " /  __ \\        ",
  "|  /    |       ",
  "|  \\___-        ",
  "-_              ",
  "  --_           ",
  "      -         "
};

const char *devuan[] = {
  " ..:::.         ",
  "    ..-==-      ",
  "        .+#:    ",
  "         =@@    ",
  "      :+%@#:    ",
  ".:=+#@@%*:      ",
  "#@@@#=:         ",
};
             

const char *gentoo[] = {
    "  .-----.       ",
    ".'    _  `.     ",
    "`.   (_)   `.   ",
    "  `.        /   ",
    " .`       .`    ",
    "/       .`      ",
    "\\____.-`        "
};

const char *manjaro[] = {
  "||||||||| ||||  ",
  "||||||||| ||||  ",
  "||||      ||||  ",
  "|||| |||| ||||  ",
  "|||| |||| ||||  ",
  "|||| |||| ||||  ",
  "|||| |||| ||||  "
};

const char *mint[] = {
  " ___________    ",
  "|_          \\   ",
  "  | | _____ |   ",
  "  | | | | | |   ",
  "  | | | | | |   ",
  "  | \\_____/ |   ",
  "  \\_________/   "
};

const char *tux[] = {
  "   .--.         ",
  "  |o_o |        ",
  "  |:_/ |        ",
  " //   \\ \\       ",
  "(|     | )      ",
  "/`\\_   _/`\\     ",
  "\\___)=(___/     "
};

typedef struct 
{
  const char *name;
  const char **logo;
} Distro;

const Distro distro_logos[] = 
{
  { "arch", arch },
  { "arco", arco },
  { "artix", artix },
  { "debian", debian },
  { "devuan", devuan },
  { "gentoo", gentoo },
  { "manjaro", manjaro },
  { "linuxmint", mint },
};

#define DISTRO_LOGO_COUNT (sizeof(distro_logos) / sizeof(distro_logos[0]))

const char **get_ascii_logo(const char *distro_id) 
{
  for (size_t i = 0; i < DISTRO_LOGO_COUNT; ++i) if (strcasecmp(distro_id, distro_logos[i].name) == 0) return distro_logos[i].logo;
  return tux;
}

char* fetchhostname() 
{
  char *buffer = malloc(64);
  if (!buffer)
  {
    perror("Error: Memory couldn't be allocated for hostname fetching.\n");
    return 0;
  }

  FILE *fptr = fopen("/etc/hostname", "r");
  if (!fptr)
  {
    FILE *hnptr = popen("uname -n", "r");
    if (hnptr == NULL) return NULL;
    fgets(buffer, 64, hnptr);
    pclose(hnptr);
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
  }
  else 
  {
    fgets(buffer, 64, fptr);
    fclose(fptr);
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
  }
}

char* fetchusername()
{
  struct passwd *pw = getpwuid(getuid());
  return pw ? pw->pw_name : "unknown";
}

char* fetchos(int Togglefetchid)
{
  FILE *fptr = fopen("/etc/os-release", "r");
  if (!fptr)
  {
    perror("Error: No os-release file located at '/etc/os-release'.\n");
    return 0;
  }

  char *buffer = malloc(64);
  if (!buffer)
  {
    perror("Error: Memory couldn't be allocated for operating-system fetching.\n");
    return 0;
  }

  if (Togglefetchid)
  {
    fgets(buffer, 64, fptr); 
    while (fgets(buffer, 64, fptr)) if (strncmp(buffer, "ID=", 3) == 0) break;
    char* id_value = buffer + 3;
    id_value[strcspn(id_value, "\n")] = '\0';    
    fclose(fptr);
    return strdup(id_value);
  }
  else 
  {
    fgets(buffer, 64, fptr);
    while (fgets(buffer, 64, fptr)) if (strncmp(buffer, "PRETTY", 3) == 0) break;
    buffer[strcspn(buffer, "\n")] = '\0';
    char* changed_buffer = strdup(buffer + 13);
    free(buffer);
    changed_buffer[strcspn(changed_buffer, "\"")] = ' ';
    fclose(fptr);
    return changed_buffer; 
  }
}

char* fetchhost()
{
  FILE *fptr = fopen("/sys/devices/virtual/dmi/id/board_name", "r");
  if (!fptr)
  {
    perror("Error: No motherboard name file located at '/sys/devices/virtual/dmi/id/board_name'.\n");
    return 0;
  }

  char *buffer = malloc(64);
  if (!buffer)
  {
    perror("Error: Memory couldn't be allocated for host fetching.\n");
    return 0;
  }

  fgets(buffer, 64, fptr);
  fclose(fptr);
  int i = strlen(buffer);
  buffer[strcspn(buffer, "\n")] = '\0';
  return buffer;
}

char* fetchkernel()
{
  struct utsname buffer;
  if (uname(&buffer) != 0) perror("Uname");
  return strdup(buffer.release);
}

double fetchuptime()
{
  FILE *fptr = fopen("/proc/uptime", "r");
  if (!fptr)
  {
    perror("Error: No uptime file located at '/proc/uptime'");
    return 1;
  }

  double uptime_seconds;
  if (fscanf(fptr, "%lf", &uptime_seconds) != 1) uptime_seconds = 0;
  fclose(fptr);
  return uptime_seconds;
}

int fetchtotalmemory()
{
  FILE *fptr = fopen("/proc/meminfo", "r");
  if (!fptr)
  {
    perror("Error: No meminfo file located at '/proc/meminfo'.\n");
    return 0;
  }

  char *buffer = malloc(64);
  if (!buffer)
  {
    perror("Error: Memory couldn't be allocated for meminfo fetching.\n");
    return 0;
  }

  int totalmemory;
  fgets(buffer, 64, fptr);
  sscanf(buffer, "MemTotal: %d kB", &totalmemory);
  fclose(fptr);
  return totalmemory;

}

int fetchusedmemory()
{
  FILE *fptr = fopen("/proc/meminfo", "r");
  if (!fptr)
  {
    perror("Error: No meminfo file located at '/proc/meminfo'.\n");
    return 0;
  }

  char *buffer = malloc(128);
  if (!buffer)
  {
    perror("Error: Memory couldn't be allocated for meminfo fetching.\n");
    return 0;
  }

  while (fgets(buffer, 128, fptr)) if (strncmp(buffer, "MemAvailable:", 13) == 0) break;
  int i;
  fclose(fptr);
  char* cut_buffer = buffer + 16;
  i = strlen(cut_buffer);
  cut_buffer[i-4] = '\0';
  int totalmemory = fetchtotalmemory();
  int availablememory = atoi(cut_buffer);
  int usedmemory = totalmemory - availablememory;
  return usedmemory;

}

int getPackages()
{
  const char *paths[] = { "/usr/bin/pacman", "/usr/bin/dpkg", "/usr/bin/emerge", "/usr/bin/dnf", "/usr/bin/zypper", "/usr/bin/xbps-query" };
  char manager[50];
  int found = 0;

  for (int i = 0; i < sizeof(paths)/sizeof(paths[0]); i++)
  {
    if (access(paths[i], X_OK) == 0)
    {
      strcpy(manager, paths[i] + 9);
      found = 1;
      break;
    }
  }

  if (!found)
  {
    perror("Error: Package Manager not found.\n");
    return 1;
  }

  if (strcmp(manager, "pacman") == 0)
  {
    FILE *fp = popen("pacman -Qq | wc -l", "r");
    if (fp == NULL)
    {
      perror("Process to find package manager failed");
      return 1;
    }

    char buffer[8];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) buffer[strcspn(buffer, "\n")] = 0;
    int pkgs = atoi(buffer);
    pclose(fp);
    return pkgs;
  }

  if (strcmp(manager, "emerge") == 0)
  {
    FILE *fp = popen("ls -d /var/db/pkg/*/* | wc -l", "r");
    if (fp == NULL)
    {
      perror("Process to find package manager failed");
      return 1;
    }

    char buffer[8];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) buffer[strcspn(buffer, "\n")] = 0;
    pclose(fp);
    int pkgs = atoi(buffer);
    return pkgs;
  }


  if (strcmp(manager, "dpkg") == 0)
  {
    FILE *fp = popen("dpkg -l | grep '^ii' | wc -l", "r");
    if (fp == NULL)
    {
      perror("Process to find package manager failed");
      return 1;
    }

    char buffer[8];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) buffer[strcspn(buffer, "\n")] = 0;
    int pkgs = atoi(buffer);
    pclose(fp);
    return pkgs;
  }

  if (strcmp(manager, "dnf") == 0)
  {
    FILE *fp = popen("dnf list installed | tail -n +2 | wc -l", "r");
    if (fp == NULL)
    {
      perror("Process to find package manager failed");
      return 1;
    }

    char buffer[8];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) buffer[strcspn(buffer, "\n")] = 0;
    int pkgs = atoi(buffer);
    pclose(fp);
    return pkgs;
  }

  if (strcmp(manager, "zypper") == 0)
  {
    FILE *fp = popen("zypper se -i | grep '^i |' | wc -l", "r");
    if (fp == NULL)
    {
      perror("Process to find package manager failed");
      return 1;
    }

    char buffer[8];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) buffer[strcspn(buffer, "\n")] = 0;
    int pkgs = atoi(buffer);
    pclose(fp);
    return pkgs;
  }

  if (strcmp(manager, "xbps-query") == 0)
  {
    FILE *fp = popen("xbps-query -l | wc -l", "r");
    if (fp == NULL)
    {
      perror("Process to find package manager failed");
      return 1;
    }

    char buffer[8];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) buffer[strcspn(buffer, "\n")] = 0;
    int pkgs = atoi(buffer);
    pclose(fp);
    return pkgs;
  }

  return 0;
}

int main(int argc, char **argv)
{
  int custom = 0; 
  const char *distro_id = NULL;

  if (argc == 2 && strcmp("-v", argv[1]) == 0)
  {
    puts("qfetch-1.0");
    return 0;
  }
  else if (argc > 2 && strcmp("--distro", argv[1]) == 0)
  {
    custom = 1; 
  }
  else if (argc != 1 && strcmp("-v", argv[1]) != 0 && strcmp("--distro", argv[1]))
  {
    puts("usage: qfetch [-v] [--distro NAME]");
    return 1;
  }

  if (custom) distro_id = argv[2];
  else distro_id = fetchos(1);
  const char **logo = get_ascii_logo(distro_id);

  char* hostname = fetchhostname();
  char* osname = fetchos(0);
  char* host = fetchhost();

  printf(BLUE "%s%s@%s\n" RESET, logo[0], fetchusername(), hostname); 
  printf(BLUE "%s" RESET BLUE "os" RESET "       %s\n", logo[1], osname);
  printf(BLUE "%s" RESET BLUE "host" RESET "     %s\n", logo[2], host);

  free(hostname);
  free(osname);
  free(host);

  char *kernel = fetchkernel();
  printf(BLUE "%s" RESET BLUE "kernel" RESET "   %s\n", logo[3], kernel);
  free(kernel);

  int uptime = fetchuptime();
  int days = uptime / (60*60*24);
  int hours = ((int)uptime / (3600)) % 24;
  int minutes = ((int)uptime / 60) % 60;
  int seconds = (int)uptime;

  if (days > 0) printf(BLUE "%s" RESET BLUE "uptime" RESET "   %dd %dh %dm\n", logo[4], days, hours, minutes);
  if (hours > 0 && days == 0) printf(BLUE "%s" RESET BLUE "uptime" RESET "   %dh %dm\n", logo[4], hours, minutes);
  if (minutes > 0 && hours == 0) printf(BLUE "%s" RESET BLUE "uptime" RESET "   %dm\n", logo[4], minutes);
  if (seconds < 60) printf(BLUE "%s" RESET BLUE "uptime" RESET "   %ds\n", logo[4], seconds);

  double usedmem = fetchusedmemory();
  double totalmem = fetchtotalmemory();
  double mempercent = (usedmem / totalmem) * 100;
  printf(BLUE "%s" RESET BLUE "memory" RESET "   %.0lfM / %.0lfM (%0.1lf%%)\n", logo[5], usedmem/1024, totalmem/1024, mempercent);
  printf(BLUE "%s" RESET BLUE "pkgs" RESET "     %d\n", logo[6], getPackages());

  if (!custom) free((void*)distro_id);
  return 0;
}
