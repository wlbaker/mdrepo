# /home/bbaker/.local/bin/protoc-c pista.proto --c_out gen

# PROTO_INC_PATH=.:./model:/home/bbaker/.local/protobuf-2.6.1/include
# PROTOCC=/home/bbaker/.local/bin/protoc-c
PROTO_INC_PATH=.:./model:/usr/local
PROTOCC=/usr/bin/protoc

${PROTOCC} --proto_path=${PROTO_INC_PATH} --java_out=../pista-core/bindings/java/model model/u3.proto
${PROTOCC} --proto_path=${PROTO_INC_PATH} --java_out=../pista-core/bindings/java/model model/imp731.proto
${PROTOCC} --proto_path=${PROTO_INC_PATH} --java_out=../pista-core/bindings/java/model model/medsys3.proto
${PROTOCC} --proto_path=${PROTO_INC_PATH} --java_out=../pista-core/bindings/java/model model/mccul.proto
${PROTOCC} --proto_path=${PROTO_INC_PATH} --java_out=../pista-core/bindings/java/model model/simu.proto
${PROTOCC} --proto_path=${PROTO_INC_PATH} --java_out=../pista-core/bindings/java/model model/dt.proto
${PROTOCC} --proto_path=${PROTO_INC_PATH} --java_out=../pista-core/bindings/java/model model/ht70.proto
