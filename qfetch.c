#define _POSIX_C_SOURCE 200809L   
#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <strings.h>    
#include <unistd.h>     
#include <pwd.h>        
#include <sys/utsname.h> 

#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define ORANGE "\033[33m"
#define BLUE   "\033[34m"
#define INDIGO "\033[35m"
#define CYAN   "\033[36m"
#define YELLOW "\033[93m"
#define VIOLET "\033[95m"
#define WHITE  "\033[97m"
#define RESET  "\033[0m"

const char *alpine[] = {
  "   /\\ /\\      ",
  "  // \\  \\     ",
  " //   \\  \\    ",
  "///    \\  \\   ",
  "//      \\  \\  ",
  "         \\    "
};

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

const char *cachyos[] = {
  "   /''''''''''''/    ",
  "  /''''''''''''/     ",
  " /''''''/            ",
  "/''''''/             ",
  "\\......\\             ",
  " \\.............../   ",
  "  \\............./    "
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

const char *elementary[] = {
  "  _______     ",
  " / ____  \\    ",
  "/  |  /  /\\   ",
  "|__\\ /  / |   ",
  "\\   /__/  /   ",
  " \\_______/     "
};

const char *fedora[] = {
  "        ,'''''.  ",
  "       |   ,.  | ",
  "       |  |  '_' ",
  "  ,....|  |..    ",
  ".'  ,_;|   ..'   ",
  "|  |   |  |      ",
  "|  ',_,'  |      ",
  " '.     ,'       ",
  "   '''''         "
};

const char *garuda[] = {
  "         _______       ",
  "      __/       \\_     ",
  "    _/     /      \\_   ",
  "  _/      /_________\\  ",
  "_/                  |  ",
  "\\     ____________     ",
  " \\_            __/     ",
  "   \\__________/        "
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

const char *hyperbola[] = {
  "    |`__.`/   ",
  "    \\____/    ",
  "    .--.      ",
  "   /    \\     ",
  "  /  ___ \\    ",
  " / .`   `.\\   ",
  "/.`      `.\\  "
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

const char *ubuntu[] = {
  "         _    ",
  "     ---(_)   ",
  " _/  ---  \\   ",
  "(_) |   |     ",
  "  \\  --- _/   ",
  "     ---(_)   "
};

const char *voidlinux[] = {
  "    _______    ",
  " _ \\______ -   ",
  "| \\  ___  \\ |  ",
  "| | /   \\ | |  ",
  "| | \\___/ | |  ",
  "| \\______ \\_|  ",
  " -_______\\     "
};

typedef struct 
{
  const char *name;
  const char **logo;
  int rows;
  const char *color;
} Distro;

const Distro distro_logos[] = 
{
    { "alpine",     alpine,     6, CYAN   },
    { "arch",       arch,       7, CYAN   },
    { "arco",       arco,       7, CYAN   },
    { "artix",      artix,      7, CYAN   },
    { "cachyos",    cachyos,    7, GREEN  },
    { "debian",     debian,     7, RED    },
    { "devuan",     devuan,     7, VIOLET },
    { "elementary", elementary, 6, WHITE },
    { "fedora",     fedora,     9, BLUE },
    { "garuda",     garuda,     8, VIOLET },
    { "gentoo",     gentoo,     7, VIOLET },
    { "hyperbola",  hyperbola,  7, WHITE  },
    { "manjaro",    manjaro,    7, GREEN  },
    { "linuxmint",  mint,       7, GREEN  },
    { "ubuntu",     ubuntu,     6, ORANGE },
    { "voidlinux",  voidlinux,  7, GREEN  }
};

#define DISTRO_COUNT (sizeof(distro_logos) / sizeof(distro_logos[0]))

const Distro *get_distro(const char *distro_id)
{
  static Distro void_distro = {"voidlinux", voidlinux, 7, GREEN};
  if (strcasecmp(distro_id, "void") == 0) return &void_distro;
  for (size_t i = 0; i < DISTRO_COUNT; i++) if (strcasecmp(distro_id, distro_logos[i].name) == 0) return &distro_logos[i];
  static Distro default_distro = { "tux", tux, 7, BLUE };
  return &default_distro;
}

typedef struct
{
  const char *name;
  const char *cmd;
} PackageManager;

const PackageManager managers[] = 
{
  { "pacman",     "pacman -Qq | wc -l"},
  { "dpkg",       "dpkg -l | grep -Ec '^(ii|rc)'"},
  { "emerge",     "ls -d /var/db/pkg/*/* 2>/dev/null | wc -l"},
  { "dnf",        "dnf list installed | wc -l"},
  { "zypper",     "zypper se --installed-only | wc -l"},
  { "xbps-query", "xbps-query -l | wc -l"},
  { "apk",        "apk info | wc -l"}
};

char* fetchhostname() 
{
  char *buffer = malloc(64);
  if (!buffer)
  {
    perror("Error: Memory couldn't be allocated for hostname fetching.\n");
    return 0;
  }

  FILE *hnptr = popen("uname -n", "r");
  if (hnptr == NULL) return NULL;
  if (fgets(buffer, 64, hnptr))
  {
    pclose(hnptr);
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
  }
  else 
  {
    perror("Error: Couldn't read hostname through 'uname -n'");
    return 0;
  }
}

char* fetchusername()
{
  struct passwd *pw = getpwuid(getuid());
  return pw ? pw->pw_name : "unknown";
}

char* fetchos(int Togglefetchid)
{
  int found = 0;
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
    if (fgets(buffer, 64, fptr))
    {
      while (fgets(buffer, 64, fptr)) if (strncmp(buffer, "ID=", 3) == 0) break;
      char* id_value = buffer + 3;
      id_value[strcspn(id_value, "\n")] = '\0';    
      fclose(fptr);
      return strdup(id_value);
    }
    else
    {
      perror("Error: Couldn't read OS ID through '/etc/os-release'");
      return 0;
    }
  }
  else 
  {
    if (fgets(buffer, 64, fptr))
    {
      if (strncmp(buffer, "PRETTY_NAME", 3) == 0) found = 1;
      if (!found) while (fgets(buffer, 64, fptr)) if (strncmp(buffer, "PRETTY_NAME", 3) == 0) break;
      buffer[strcspn(buffer, "\n")] = '\0';
      char* changed_buffer = strdup(buffer + 13);
      free(buffer);
      changed_buffer[strcspn(changed_buffer, "\"")] = ' ';
      fclose(fptr);
      return changed_buffer; 
    }
    else
    {
      perror("Error: Couldn't read OS name through '/etc/os-release'");
      return 0;
    }
  }
  return 0;
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

  if (fgets(buffer, 64, fptr))
  {
    fclose(fptr);
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
  }
  else
  {
    perror("Error: Couldn't read host through '/sys/devices/virtual/dmi/id/board_name'");
    return 0;
  }
  return 0;
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
  if (fgets(buffer, 64, fptr))
  {
    sscanf(buffer, "MemTotal: %d kB", &totalmemory);
    fclose(fptr);
    return totalmemory;
  }
  else
  {
    perror("Error: Couldn't read total memory through '/proc/meminfo'");
    return 0;
  }
  return 0;
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
  char cmd[64];
  char path[64];
  size_t i;
  for (i = 0; i < sizeof(managers)/sizeof(managers[0]); i++)
  {
    snprintf(cmd, sizeof(cmd), "which %s 2>/dev/null", managers[i].name);
    FILE *fptr = popen(cmd, "r");
    if (!fptr)
    {
      perror("popen failed");
      return -1;
    }
    if (fgets(path, 64, fptr))
    {
      pclose(fptr);
      break;
    }
    pclose(fptr);
  }

  if (i == sizeof(managers)/sizeof(managers[0])) return -1;

  FILE *fptr = popen(managers[i].cmd, "r");
  if (!fptr) return -1;

  char buffer[16];
  if (!fgets(buffer, 16, fptr))
  {
    pclose(fptr);
    return -1;
  }
  pclose(fptr);
  return atoi(buffer);
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
  const Distro *distro = get_distro(distro_id);

  char* hostname = fetchhostname();
  char* osname = fetchos(0);
  char* host = fetchhost();

  printf("%s%s%s@%s%s\n", distro->color, distro->logo[0], fetchusername(), hostname, RESET);
  printf("%s%s%sos%s       %s\n", distro->color, distro->logo[1], distro->color, RESET, osname);
  printf("%s%s%shost%s     %s\n", distro->color, distro->logo[2], distro->color, RESET, host);

  free(hostname);
  free(osname);
  free(host);

  char *kernel = fetchkernel();
  printf("%s%s%skernel%s   %s\n", distro->color, distro->logo[3], distro->color, RESET, kernel);
  free(kernel);

  int uptime = fetchuptime();
  int days = uptime / (60*60*24);
  int hours = ((int)uptime / 3600) % 24;
  int minutes = ((int)uptime / 60) % 60;
  int seconds = (int)uptime;

  if (days > 0)
      printf("%s%s%suptime%s   %dd %dh %dm\n", distro->color, distro->logo[4], distro->color, RESET, days, hours, minutes);
  if (hours > 0 && days == 0)
      printf("%s%s%suptime%s   %dh %dm\n", distro->color, distro->logo[4], distro->color, RESET, hours, minutes);
  if (minutes > 0 && hours == 0 && days == 0)
      printf("%s%s%suptime%s   %dm\n", distro->color, distro->logo[4], distro->color, RESET, minutes);
  if (seconds < 60)
      printf("%s%s%suptime%s   %ds\n", distro->color, distro->logo[4], distro->color, RESET, seconds);

  double usedmem = fetchusedmemory();
  double totalmem = fetchtotalmemory();
  double mempercent = (usedmem / totalmem) * 100;
  printf("%s%s%smemory%s   %.0lfM / %.0lfM (%0.1lf%%)\n", distro->color, distro->logo[5], distro->color, RESET, usedmem/1024, totalmem/1024, mempercent);
  if (distro->rows >= 7) printf("%s%s%spkgs%s     %d\n", distro->color, distro->logo[6], distro->color, RESET, getPackages());
  else printf("%s              pkgs%s     %d\n", distro->color, RESET, getPackages());

  if (distro->rows >= 8) printf("%s%s%s%s\n", distro->color, distro->logo[7], distro->color, RESET);
  if (distro->rows == 9) printf("%s%s%s%s\n", distro->color, distro->logo[8], distro->color, RESET);

  if (!custom) free((void*)distro_id);
  return 0;

}
