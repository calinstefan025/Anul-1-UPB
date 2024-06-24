FROM jokeswar/base-ctl

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

RUN echo "Hello from Docker"

RUN apt update -y

RUN apt install -y octave python3

COPY ./checker ${CHECKER_DATA_DIRECTORY}
