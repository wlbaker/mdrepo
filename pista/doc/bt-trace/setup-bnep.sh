#!/bin/bash

br=bnep0

[[ -n "$(brctl show $br 2>&1 1>/dev/null)" ]] && {
  brctl addbr $br
  brctl setfd $br 0
  brctl stp $br off
  ip addr add 10.5.0.5/16 dev $br
  ip link set $br up
}

# local records
sdptool records local
# sdptool del 0x10004
# sdptool del 0x10003
# sdptool del 0x10001
# sdptool del 0x10002
# sdptool del 0x10006
# sdptool del 0x10005

