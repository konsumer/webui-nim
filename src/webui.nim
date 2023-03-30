{.passC: "-Isrc/clib/include".}
{.compile: "src/clib/src/webui.c".}
{.compile: "src/clib/src/mongoose.c".}

const
  WEBUI_MAX_ARRAY* = (1024)
  WEBUI_MIN_PORT* = (10000)
  WEBUI_MAX_PORT* = (65500)
  WEBUI_MAX_BUF* = (1024000)
  WEBUI_DEFAULT_PATH* = "."
  WEBUI_DEF_TIMEOUT* = (8)

type
  window_core_t* {.bycopy.} = object
    window_number*: cuint
    server_running*: bool
    connected*: bool
    server_handled*: bool
    multi_access*: bool
    server_root*: bool
    server_port*: cuint
    is_bind_all*: bool
    url*: cstring
    e*: ptr event_t
    html*: cstring
    html_cpy*: cstring
    icon*: cstring
    icon_type*: cstring
    CurrentBrowser*: cuint
    browser_path*: cstring
    profile_path*: cstring
    connections*: cuint
    runtime*: cuint
    detect_process_close*: bool
    server_thread*: pointer

  window_t* {.bycopy.} = object
    core*: window_core_t
    path*: cstring

  event_t* {.bycopy.} = object
    window_id*: cuint
    element_id*: cuint
    element_name*: cstring
    window*: ptr window_t
    data*: pointer
    response*: pointer

  javascript_result_t* {.bycopy.} = object
    error*: bool
    length*: cuint
    data*: cstring

  script_t* {.bycopy.} = object
    script*: cstring
    timeout*: cuint
    result*: javascript_result_t

  cb_t* {.bycopy.} = object
    win*: ptr window_t
    internal_id*: cstring
    element_name*: cstring
    data*: pointer

  cmd_async_t* {.bycopy.} = object
    win*: ptr window_t
    cmd*: cstring

  custom_browser_t* {.bycopy.} = object
    app*: cstring
    arg*: cstring
    auto_link*: bool

  browser_t* = enum
    any=0,
    chrome=1,
    firefox=2,
    edge=3,
    safari=4,
    chromium = 5,
    opera = 6,
    brave = 7,
    vivaldi = 8,
    epic = 9,
    yandex = 10,
    current = 98,
    custom = 99

  runtime_t* = enum
    none=0,
    deno=1,
    nodejs=2

  t* {.bycopy.} = object
    servers*: cuint
    connections*: cuint
    process*: cuint
    custom_browser*: ptr custom_browser_t
    wait_for_socket_window*: bool
    html_elements*: array[WEBUI_MAX_ARRAY, cstring]
    used_ports*: array[WEBUI_MAX_ARRAY, cuint]
    last_window*: cuint
    startup_timeout*: cuint
    use_timeout*: bool
    timeout_extra*: bool
    exit_now*: bool
    run_responses*: array[WEBUI_MAX_ARRAY, cstring]
    run_done*: array[WEBUI_MAX_ARRAY, bool]
    run_error*: array[WEBUI_MAX_ARRAY, bool]
    run_last_id*: cuint
    mg_mgrs*: array[WEBUI_MAX_ARRAY, pointer]
    mg_connections*: array[WEBUI_MAX_ARRAY, pointer]
    browser*: browser_t
    runtime*: runtime_t
    initialized*: bool
    e*: ptr event_t
    cb_interface*: pointer
    cb_interface_all*: pointer
    executable_path*: cstring
    ptr_list*: array[WEBUI_MAX_ARRAY, pointer]
    ptr_position*: cuint
    ptr_size*: array[WEBUI_MAX_ARRAY, csize_t]
  
  script_interface_t* {.bycopy.} = object
    script*: cstring
    timeout*: cuint
    error*: bool
    length*: cuint
    data*: cstring

var webui*: t

{.push importc:"webui_$1".}

proc new_window*(): ptr window_t {.cdecl.}
proc `bind`*(win: ptr window_t; element: cstring; `func`: proc (e: ptr event_t) {.cdecl.}): cuint {.cdecl.}
proc bind_all*(win: ptr window_t; `func`: proc (e: ptr event_t) {.cdecl.}) {.cdecl.}
proc show*(win: ptr window_t; content: cstring; browser: browser_t): bool {.cdecl.}
proc wait*() {.cdecl.}
proc close*(win: ptr window_t) {.cdecl.}
proc exit*() {.cdecl.}
proc script*(win: ptr window_t; script: ptr script_t) {.cdecl.}
proc script_cleanup*(script: ptr script_t) {.cdecl.}
proc script_runtime*(win: ptr window_t; runtime: cuint) {.cdecl.}
proc get_int*(e: ptr event_t): clonglong {.cdecl.}
proc get_string*(e: ptr event_t): cstring {.cdecl.}
proc get_bool*(e: ptr event_t): bool {.cdecl.}
proc return_int*(e: ptr event_t; n: clonglong) {.cdecl.}
proc return_string*(e: ptr event_t; s: cstring) {.cdecl.}
proc return_bool*(e: ptr event_t; b: bool) {.cdecl.}
proc new_server*(win: ptr window_t; path: cstring): cstring {.cdecl.}
proc open*(win: ptr window_t; url: cstring; browser: cuint): bool {.cdecl.}
proc is_any_window_running*(): bool {.cdecl.}
proc is_app_running*(): bool {.cdecl.}
proc is_shown*(win: ptr window_t): bool {.cdecl.}
proc set_timeout*(second: cuint) {.cdecl.}
proc set_icon*(win: ptr window_t; icon_s: cstring; type_s: cstring) {.cdecl.}
proc multi_access*(win: ptr window_t; status: bool) {.cdecl.}
proc clean_mem*(p: pointer) {.cdecl.}
proc bind_interface*(win: ptr window_t; element: cstring; `func`: proc (a1: cuint; a2: cuint; a3: cstring; a4: ptr window_t; a5: cstring; a6: cstringArray) {.cdecl.}): cuint {.cdecl.}
proc script_interface*(win: ptr window_t; script: cstring; timeout: cuint; error: ptr bool; length: ptr cuint; data: cstringArray) {.cdecl.}
proc script_interface_struct*(win: ptr window_t; js_int: ptr script_interface_t) {.cdecl.}

{.pop.}
