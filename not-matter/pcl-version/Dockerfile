FROM ubuntu:bionic

RUN apt-get -qq update \
  && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    cmake \
    git-core \
    libboost-all-dev \
    libeigen3-dev \
    libflann-dev \
    libgl-dev \
    libgtest-dev \
    make \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /work
COPY Makefile /work
RUN make init
COPY . /work

ENTRYPOINT ["make"]
CMD ["test"]
