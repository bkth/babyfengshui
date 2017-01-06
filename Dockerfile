FROM debian:latest

RUN dpkg --add-architecture i386
RUN apt-get -y update

RUN groupadd -g 1000 fengshui
RUN useradd -g fengshui -s /bin/bash fengshui

# socat
RUN apt-get -y install socat libc6:i386 libncurses5:i386 libstdc++6:i386


ADD babyfengshui /chall/
ADD start_server.sh /start/
ADD flag.txt /chall/

RUN chmod 705 /chall/babyfengshui
RUN chmod 704 /chall/flag.txt
RUN chmod 700 /start/start_server.sh

CMD cd /chall/; /start/start_server.sh 1456; /bin/bash



