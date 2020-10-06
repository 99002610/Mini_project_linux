## Problem description
Assume there are three types of threads in the system, A, B, and C.
There is buffer with size of 1 between A and B, where A writes data into the buffer and B reads data from the buffer;
and another buffer of size 1 between B and C,
where B writes the data read from the first buffer into this one, and C reads the data from it.

You are asked to implement such a system with 1) busy waiting synchronization mechanism; 2) semaphore. 
Compare the above two implementations in terms of the performance (execution time), and discussion on the test cases.


## How to build
```
g++ main.c -lpthread -o run-me
g++ main_busy_waiting.c -lpthread -o run-me-2
```

## How to run
After you build it, navigate to where the file main.c/run is located and run
```
./run-me
./run-me-2 # run the other one after you stop this one by interrupting it with Ctrl + C
```

## Program overview
Here are two kind of implementation of the chained producer&consumer problem, 
busy-waiting and non-busy-waiting (semaphore) implementations.    

N_LOOP is defined to decide when to stop the infinite loop, in other words, it keeps producing and consuming until C has
consumed N_LOOP times.    

Elapsed times(in nanosecond) when process C has consumed for i times is stored in the csv files, 
statistics_non-busy-waiting.csv and statistics_busy-waiting.csv respectively, where i is from 1 to N_LOOP. We are able
to run the executable file for as many times as we want to compare the performance between these two implementation. 
Every time you run the program, the statistics will be appended to the files unless you delete it manually. 

## Algorithm explanation
Overall, it is a producer and consumer problem with two buffers. 
Therefore, the algorithm could be briefly explained below. 
(The explanation is based on the non-busy-waiting implementation with the semaphores mechanism, however, 
the design is the same as the busy-waiting.)

We have two pair of empty and full semaphores: sem_t empty[2], full[2], two mutexes sem_t mutex[2] 
and two buffer in size of 1: char buffer[2].

* Process A
```
while(1){
    // codes to write buffer 1
    P(&empty[0]);
    P(&mutex[0]);
    /* write buffer[0] */
    V(&mutex[0]);
    V(&full[0]);

}
```


* Process B
```
while(1){
    // codes to read buffer 1
    P(&full[0]);
    P(&mutex[0]);
    /* read buffer[0] */
    V(&mutex[0]);
    V(&empty[0]);


    // codes to write buffer 2
    P(&empty[1]);
    P(&mutex[1]);
    /* read buffer[0] */
    V(&mutex[1]);
    V(&full[1]);

}
```

* Process C
```
while(1){
    // codes to read buffer 2
    P(&full[1]);
    P(&mutex[1]);
    /* read buffer[1] */
    V(&mutex[1]);
    V(&empty[1]);

}
```

## Sample standard output
Use "Ctrl + C" to stop(interrupt) the program.
```
Process A is writing A into buffer1
Process B is reading A from buffer1
Process A is writing A into buffer1
Process B is writing A into buffer2
Process B is reading A from buffer1
Process C is reading A from buffer2
Process A is writing A into buffer1
Process B is writing A into buffer2
Process B is reading A from buffer1
Process C is reading A from buffer2
...
```

## Sample statistics of elapsed time (in nanosecond)
For example, I have run these two program fors 50 times respectively with the shell script run.sh, and got the data. 
Here are the first 10 lines of each file shown below. Full data could be found in the two statistics files.

Obviously, the non-busy-waiting mechanism does significantly improve the performance.
* non-busy-waiting implementation (semaphore)
```csv
884381,1320087,1776899,2197311,2620130,3064447,3505218,4022857,4453379,4958352
872842,1303938,1743864,2229157,2648448,3050725,3466779,3894133,4359540,4946338
944233,1405847,1934223,2391737,2873201,3301931,3739123,4198734,4664192,5163006
879081,1340624,1752073,2212620,2721976,3203820,3675558,4118919,4544658,5034626
954380,1373388,1806131,2241150,2683261,3140093,3573187,4003754,4423079,4916640
914342,1280662,1701832,2178192,2584209,3015113,3435224,3880538,4323717,4852430
1102524,1539159,2010963,2442338,2883225,3337149,3802313,4220768,4669885,5173197
819910,1211143,1635598,2096865,2537779,2993693,3426846,3850955,4272131,4741689
878444,1297815,1725818,2169975,2627024,3126306,3550129,4094917,4598587,5273872
1071067,1632370,2208357,2696271,3162230,3635257,4098657,4781527,5243652,5700173
```

* busy-waiting implementation
```csv
12928758,13146038,16712603,13565236,20755996,13993096,20794170,14427731,20728045,20756168
24348266,24343833,24335552,24335868,21377940,28361103,22438476,21998246,28337601,22418927
16737129,16772185,16744864,244457333,13748600,116894183,116798893,116794662,14671597,14893743
227759130,12749159,228234598,13206442,13426424,228061139,13863544,14082803,227688655,14504182
20905288,21122187,21331137,21540742,21756816,211850918,84740531,22389621,84732448,22812394
20576098,20796924,21021795,21237997,21459188,60416916,60425146,60429011,22337968,187103751
39472425,15856870,161951688,161860346,16527509,161909795,16956927,17162467,161801054,17921712
14973790,17734579,13503831,142413783,13951895,14185624,14407855,14639647,142360703,142254670
125623394,247640225,247614778,375331689,375319924,375328842,375299655,375260901,239612462,375230533
10397122,10610960,246161081,11022005,122219593,11439978,246290900,11869901,12076029,12288842
```

## Performance analyses
Please refer to the file performance_analyses.md for more details.

According to the smaple statistics shown above, we can calculate the average accumulative elapsed time and
the standard derivation for each mechanism.

* Non-busy-waiting/semaphore

|Item|1|2|3|4|5|6|7|8|9|10|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|busy-waiting|51372140.00|40077296.00|99761192.70|102897144.10|64054388.50|122244159.40|97201609.70|66905499.00|95434656.20|83018492.20|
|non-busy-waiting|932120.40|1370503.30|1829575.80|2285561.60|2734148.30|3186853.40|3627303.40|4106710.20|4555282.00|5076032.30|

![Perfomance_analyses_of_two_kinds_of_implementation_10](https://avxvxg.by.files.1drv.com/y4mE1te3FMunG7H5KCDOZ8BHT6tZuZIeQgVLiO4kHF9WBcl8_FBs_MTe8kChWthJsS2AajwRYkWidbF4SLkHjP2vTH9i4wCiKPo0zdKhpEwYse_bZ8W5xhnHAE44d2ff-FUYi-N7rdVp8R4aVRV5ZfSwJa0cHGPS3W6KB3D1Tmwq0F5-TDIKK_TAgZuX9BffhAxYO3Ko1fnB0OLc3M1UAZBhQ?width=640&height=480&cropmode=none)