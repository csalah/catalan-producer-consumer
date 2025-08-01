
# Shared Memory Catalan Producer-Consumer

Inter process communication in C using **System V shared memory**. One process (the producer) generates a sequence of **Catalan numbers** and writes them to shared memory. Another process (the consumer) waits until the data is ready and then reads it.

Catalan numbers are generated using the recursive formula:
Cₙ₊₁ = Cₙ * 2(2n + 1) / (n + 2)

---

## Files

- `producteur.c` — produces Catalan numbers and writes them to shared memory  
- `consommateur.c` — waits for the producer to finish and reads the data

---

## How to Compile

```bash
gcc -o producteur producteur.c
gcc -o consommateur consommateur.c
```
`Run the producer in one terminal`
```bash
./producteur <number of values>
```

`Run the consumer in another terminal`
```bash
./consommateur
```

## Clean up shared memory (if needed)

List shared memory
```bash
ipcs -m
```
Replace <shmid> with ID
```bash
ipcrm -m <shmid>
```


