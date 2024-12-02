FROM debian:stretch
LABEL maintainer="Keymaker Developers <dev@keymaker.org>"
LABEL description="Dockerised KeymakerCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
