FROM emscripten/emsdk:2.0.4

WORKDIR /
COPY /src /src
COPY /bin /bin

RUN mkdir -p public/js/
RUN bin/emcc
RUN mv public/js out/
