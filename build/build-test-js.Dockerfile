FROM emscripten/emsdk:2.0.29

COPY /src /src

WORKDIR /
RUN     mkdir out/
RUN     emcc src/hello.c \
          --use-preload-plugins \
          -o out/test.js \
          -s EXPORTED_RUNTIME_METHODS=['FS'] \
          -s MODULARIZE=1 \
          -s EXPORT_NAME=test
