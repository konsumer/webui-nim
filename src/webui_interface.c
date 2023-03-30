// THIS iS NOT PART OF NIM BINDINGS
// It's a cleaned up interface for generating nim binding mroe quickly
// c2nim src/webui_interface.c --prefix:webui_ --cdecl

#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define WEBUI_MAX_ARRAY (1024)
#define WEBUI_MIN_PORT (10000)
#define WEBUI_MAX_PORT (65500)
#define WEBUI_MAX_BUF (1024000)
#define WEBUI_DEFAULT_PATH "."
#define WEBUI_DEF_TIMEOUT (8)

// -- Structs -------------------------
typedef struct webui_event_t {
} webui_event_t;

typedef struct webui_timer_t {
  struct timespec start;
  struct timespec now;
} webui_timer_t;

typedef struct webui_window_core_t {
  unsigned int window_number;
  bool server_running;
  bool connected;
  bool server_handled;
  bool multi_access;
  bool server_root;
  unsigned int server_port;
  bool is_bind_all;
  char* url;
  struct webui_event_t* e;
  const char* html;
  const char* html_cpy;
  const char* icon;
  const char* icon_type;
  unsigned int CurrentBrowser;
  char* browser_path;
  char* profile_path;
  unsigned int connections;
  unsigned int runtime;
  bool detect_process_close;
  pthread_t server_thread;
} webui_window_core_t;

typedef struct webui_window_t {
  webui_window_core_t core;
  char* path;
} webui_window_t;

typedef struct webui_event_t {
  unsigned int window_id;
  unsigned int element_id;
  char* element_name;
  webui_window_t* window;
  void* data;
  void* response;
} webui_event_t;

typedef struct webui_javascript_result_t {
  bool error;
  unsigned int length;
  const char* data;
} webui_javascript_result_t;

typedef struct webui_script_t {
  const char* script;
  unsigned int timeout;
  webui_javascript_result_t result;
} webui_script_t;

typedef struct webui_cb_t {
  webui_window_t* win;
  char* webui_internal_id;
  char* element_name;
  void* data;
} webui_cb_t;

typedef struct webui_cmd_async_t {
  webui_window_t* win;
  char* cmd;
} webui_cmd_async_t;

typedef struct webui_custom_browser_t {
  char* app;
  char* arg;
  bool auto_link;
} webui_custom_browser_t;

typedef struct webui_browser_t {
  unsigned int any;       // 0
  unsigned int chrome;    // 1
  unsigned int firefox;   // 2
  unsigned int edge;      // 3
  unsigned int safari;    // 4
  unsigned int chromium;  // 5
  unsigned int opera;     // 6
  unsigned int brave;     // 7
  unsigned int vivaldi;   // 8
  unsigned int epic;      // 9
  unsigned int yandex;    // 10
  unsigned int current;   // x
  unsigned int custom;    // 99
} webui_browser_t;

typedef struct webui_runtime_t {
  unsigned int none;    // 0
  unsigned int deno;    // 1
  unsigned int nodejs;  // 2
} webui_runtime_t;

typedef struct webui_t {
  unsigned int servers;
  unsigned int connections;
  unsigned int process;
  webui_custom_browser_t* custom_browser;
  bool wait_for_socket_window;
  char* html_elements[WEBUI_MAX_ARRAY];
  unsigned int used_ports[WEBUI_MAX_ARRAY];
  unsigned int last_window;
  unsigned int startup_timeout;
  bool use_timeout;
  bool timeout_extra;
  bool exit_now;
  const char* run_responses[WEBUI_MAX_ARRAY];
  bool run_done[WEBUI_MAX_ARRAY];
  bool run_error[WEBUI_MAX_ARRAY];
  unsigned int run_last_id;
  struct mg_mgr* mg_mgrs[WEBUI_MAX_ARRAY];
  struct mg_connection* mg_connections[WEBUI_MAX_ARRAY];
  webui_browser_t browser;
  webui_runtime_t runtime;
  bool initialized;
  webui_event_t* e;
  void* cb_interface;
  void* cb_interface_all;
  char* executable_path;
  void* ptr_list[WEBUI_MAX_ARRAY];
  unsigned int ptr_position;
  size_t ptr_size[WEBUI_MAX_ARRAY];
} webui_t;

// -- Definitions ---------------------
webui_t webui;
// Create a new window object
webui_window_t* webui_new_window();
// Bind a specific HTML Element-ID click event with a function
unsigned int webui_bind(webui_window_t* win,
                        const char* element,
                        void (*func)(webui_event_t* e));
// Bind all clicks event with a function
void webui_bind_all(webui_window_t* win, void (*func)(webui_event_t* e));
// Show a window using a static HTML script, or a file name in the same working
// directory. If the window is already opened then it will be refreshed with the
// new content
bool webui_show(webui_window_t* win, const char* content);
// Wait until all opened windows get closed
void webui_wait();
// Close a specific window
void webui_close(webui_window_t* win);
// Close all opened windows
void webui_exit();

// Run a JavaScript
void webui_script(webui_window_t* win, webui_script_t* script);
void webui_script_cleanup(webui_script_t* script);
void webui_script_runtime(webui_window_t* win, unsigned int runtime);
long long int webui_get_int(webui_event_t* e);
const char* webui_get_string(webui_event_t* e);
bool webui_get_bool(webui_event_t* e);
void webui_return_int(webui_event_t* e, long long int n);
void webui_return_string(webui_event_t* e, char* s);
void webui_return_bool(webui_event_t* e, bool b);

const char* webui_new_server(webui_window_t* win, const char* path);
bool webui_open(webui_window_t* win, const char* url, unsigned int browser);
bool webui_is_any_window_running();
bool webui_is_app_running();
bool webui_is_shown(webui_window_t* win);
void webui_set_timeout(unsigned int second);
void webui_set_icon(webui_window_t* win,
                    const char* icon_s,
                    const char* type_s);
void webui_multi_access(webui_window_t* win, bool status);
void webui_clean_mem(void* p);

// -- Interface -----------------------
// Used by other languages to create WebUI wrappers
typedef struct webui_script_interface_t {
  char* script;
  unsigned int timeout;
  bool error;
  unsigned int length;
  const char* data;
} webui_script_interface_t;
unsigned int webui_bind_interface(webui_window_t* win,
                                  const char* element,
                                  void (*func)(unsigned int,
                                               unsigned int,
                                               char*,
                                               webui_window_t*,
                                               char*,
                                               char**));
void webui_script_interface(webui_window_t* win,
                            const char* script,
                            unsigned int timeout,
                            bool* error,
                            unsigned int* length,
                            char** data);
void webui_script_interface_struct(webui_window_t* win,
                                   webui_script_interface_t* js_int);
