# This is just an example to get you started. You may wish to put all of your
# tests into a single file, or separate them into multiple `test1`, `test2`
# etc. files (better names are recommended, just make sure the name starts with
# the letter 't').
#
# To run these tests, simply execute `nimble test`.

import unittest

import webui

test "can open window with C bindings":
  var my_window = webui.new_window()
  discard webui.show(my_window, "<html>Hello</html>", webui.browser_t.any);
  webui.wait();
