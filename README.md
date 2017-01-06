# babyfengshui

This was a pwnable worth 150 pts that I wrote for the [33C3CTF](https://ctftime.org/event/404)  organised by [Eat, Sleep, Pwn, Repeat](https://ctftime.org/team/15712)

Every script used for the deployment of the challenge are included, you can just execute

```bash
make clean && make all
./build_docker.sh && ./run_docker.sh
```

and try out the exploit by running

```
python exploit.py local
```

## Vulnerability (Spoilers)

The vulnerability in the binary is a custom overflow check which makes a wrong assumptions that two subsequent allocations on the heap will be placed next to each other


