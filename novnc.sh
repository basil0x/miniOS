#!/bin/sh

# TODO REFACTOR
/~/noVNC/./utils/novnc_proxy --vnc localhost:5900 --listen localhost:6081 </dev/null &>/dev/null &
firefox http://localhost:6081/vnc.html </dev/null &>/dev/null &

