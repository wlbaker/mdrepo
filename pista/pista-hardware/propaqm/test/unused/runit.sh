#!/bin/sh

# gdb ./test_propaqm -ex "set args AP14E001105.X-Series.device.ZOLL.local -u zolldata:Chocolate2016"
# ./test_propaqm AP14E001105.X-Series.device.ZOLL.local -u zolldata:Chocolate2016
gdb ./test_propaqm -ex "set args AP14E001105.X-Series.device.ZOLL.local -u zolldata:MDARK2018"

# gdb ./test_propaqm -ex "set args 192.168.50.100 -u zolldata:MDARK2018"
# ./test_propaqm 192.168.50.100 -u zolldata:MDARK2018

