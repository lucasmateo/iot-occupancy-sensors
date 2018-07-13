#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "esp_log.h"
#include "lwip/dns.h"

#define WEB_SERVER "google.com"
#define WEB_PORT 9000
#define WEB_URL "www.google.com"

static const char *TAG = "http request";


static const char *GET_REQUEST = "GET " WEB_URL " HTTP/1.0\r\n"
    "Host: "WEB_SERVER"\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "\r\n";

int get_request(){
  const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
  };
  struct addrinfo *res;
  struct in_addr *addr;
  int s, r;
  char recv_buf[64];

  int err = getaddrinfo(WEB_SERVER, "80", &hints, &res);

  if(err != 0 || res == NULL) {
      ESP_LOGE(TAG, "DNS lookup failed err=%d res=%p", err, res);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      return 1;
  }

  /* Code to print the resolved IP.

     Note: inet_ntoa is non-reentrant, look at ipaddr_ntoa_r for "real" code */
  addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
  ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", inet_ntoa(*addr));

  s = socket(res->ai_family, res->ai_socktype, 0);
  if(s < 0) {
      ESP_LOGE(TAG, "... Failed to allocate socket.");
      freeaddrinfo(res);
      return 1;
  }
  ESP_LOGI(TAG, "... allocated socket");

  if(connect(s, res->ai_addr, res->ai_addrlen) != 0) {
      ESP_LOGE(TAG, "... socket connect failed errno=%d", errno);
      close(s);
      freeaddrinfo(res);
      return 1;
  }

  ESP_LOGI(TAG, "... connected");
  freeaddrinfo(res);

  if (write(s, GET_REQUEST, strlen(GET_REQUEST)) < 0) {
      ESP_LOGE(TAG, "... socket send failed");
      close(s);
      return 1;
  }
  ESP_LOGI(TAG, "... socket send success");

  struct timeval receiving_timeout;
  receiving_timeout.tv_sec = 5;
  receiving_timeout.tv_usec = 0;
  if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout,
          sizeof(receiving_timeout)) < 0) {
      ESP_LOGE(TAG, "... failed to set socket receiving timeout");
      close(s);
      return 1;
  }
  ESP_LOGI(TAG, "... set socket receiving timeout success");

  /* Read HTTP response */
  do {
      bzero(recv_buf, sizeof(recv_buf));
      r = read(s, recv_buf, sizeof(recv_buf)-1);
      for(int i = 0; i < r; i++) {
          putchar(recv_buf[i]);
      }
  } while(r > 0);

  ESP_LOGI(TAG, "... done reading from socket. Last read return=%d errno=%d\r\n", r, errno);
  close(s);

  return 1;
}

int post_request(){
	return 1;
}
