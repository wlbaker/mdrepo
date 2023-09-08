#!/bin/sh

# /home/bbaker/.local/bin/protoc-c pista.proto --c_out gen

# PROTO_INC_PATH=.:./model:/home/bbaker/.local/protobuf-2.6.1/include
# PROTOCC=/home/bbaker/.local/bin/protoc-c
PROTO_INC_PATH=.:./model:/usr/local
PROTOCC=/usr/bin/protoc-c

if [ ! -f "$PROTOCC" ]; then
	PROTOCC=`which protoc-c`
fi

# PROTOCC=/usr/x86_64-w64-mingw32/sys-root/mingw/bin/protoc-c
# ${PROTOCC} --proto_path=${PROTO_INC_PATH} --c_out=../pista-hardware model/dt.proto

# /home/bbaker/.local/bin/protoc --proto_path=${PROTO_INC_PATH} --java_out=jgen pista.proto
# /home/bbaker/.local/bin/protoc-c --proto_path=${PROTO_INC_PATH} t.proto --c_out gen

# /home/bbaker/.local/bin/protoc-c --proto_path=${PROTO_INC_PATH} --c_out=../pista-hardware/model pista.proto
PROTOC_OPTIONS=-"-proto_path=${PROTO_INC_PATH}"
PROTOC_OPTIONS=

${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/ht70     ht70.proto
# ${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/pista  pista.proto
${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/u3       u3.proto
${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/imp731   imp731.proto
${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/medsys3  medsys3.proto
${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/mcc-ul   mccul.proto
${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/simu     simu.proto
${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/dt       dt.proto
${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/propaqm  propaqm.proto
${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/bmp180   bmp180.proto

${PROTOCC} ${PROTOC_OPTIONS} --c_out=../../pista-hardware/infinity infinity.proto

