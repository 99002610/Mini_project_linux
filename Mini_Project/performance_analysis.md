## Performance analyses
With the statistics files, we can calculate the average accumulative elapsed time and 
the standard derivation for each mechanism. Observing the following charts and recalling the implementation details, 
we can conclude that the busy-waiting mechanism is able to work on the issue about shared data synchronization. 
However, it wastes a lot of time grasping the CPU. In addition, for some reason, the behavior of it is pretty unstable 
and even much weird in our experiments. Non-busy-waiting mechanism(semaphore mechanism) is a profound breakthrough 
becuase it does improve the performance a lot.  

1. N_LOOP = 10

![Performance_of_two_kinds_of_implementation_10](https://avxvxg.by.files.1drv.com/y4mE1te3FMunG7H5KCDOZ8BHT6tZuZIeQgVLiO4kHF9WBcl8_FBs_MTe8kChWthJsS2AajwRYkWidbF4SLkHjP2vTH9i4wCiKPo0zdKhpEwYse_bZ8W5xhnHAE44d2ff-FUYi-N7rdVp8R4aVRV5ZfSwJa0cHGPS3W6KB3D1Tmwq0F5-TDIKK_TAgZuX9BffhAxYO3Ko1fnB0OLc3M1UAZBhQ?width=640&height=480&cropmode=none)

* Non-busy-waiting/semaphore    

|Item|1|2|3|4|5|6|7|8|9|10|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|AEVERAGE|932120.40|1370503.30|1829575.80|2285561.60|2734148.30|3186853.40|3627303.40|4106710.20|4555282.00|5076032.30|
|STDEV|90296.00|126882.57|172793.00|177417.17|188683.79|195322.46|209303.02|270088.13|279048.05|271880.42|

![Performance_analyses_semaphore_10](https://a1xvxg.by.files.1drv.com/y4m9aiWJL2BDc_uAH8tHYx33mORAwIx8Qvv5-sJ_5BsehRahJR8idx1RnZ3EsNxqjJIee1stC_W7vhV0-JDL9UnFTpPEVnpuzZtHKJKsh_QMbZxA4j170m4lPCyvf2TZPyNl_eYH0AUTgmhC768Ma8iog9aKlENuezOA4S86frCweRBZtKoUXTXoa1dk26WD7KBqUdr_qw9gAny7onWgMT-Sg?width=840&height=536&cropmode=none)

* Busy-waiting

|Item|1|2|3|4|5|6|7|8|9|10|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|AEVERAGE|51372140.00|40077296.00|99761192.70|102897144.10|64054388.50|122244159.40|97201609.70|66905499.00|95434656.20|83018492.20|
|STDEV|70754196.43|73052704.85|106945463.12|126149250.17|114227753.82|121650495.98|121620927.78|113231037.71|90613342.55|119944286.88|

![Performance_analyses_busy-waiting_10](https://p1q6ug.by.files.1drv.com/y4m2s4JDA9ENqIUcy55cx16gSxP35N6Q26qbewTYL3c2qVlZgj0pR1i4qEHe7ULpvpjs1kkf-aCw8xfZz2rGyyrAGUH3gK4a_fzTi8r6UWIb3_zhILvlVA2hbR9AVS0Ao6_fFe4xmCteDU_iuoNGI9L1fXBNsecLZ5hfYtR6MBr_f7R32UMo6YihAqkz6ChmBUE6HHGVka3y-gPpf23D9a_kw?width=640&height=480&cropmode=none)




2. N_LOOP = 50

![Performance_of_two_kinds_of_implementation_50](https://afxvxg.by.files.1drv.com/y4mKKphq936EK4SxX36uN9xOtcFGMskeWHidrPIUmUtb83clEuRloUaTynEwsHN6_3GUYx83I4FLVj1AglefpwqlwhniMsLdTo9jRjOOgh3_WNew41UhMBg-lBYs_WsbLNftJPFRDItoU70St4aWLcKYEOq9UAocYCJOWfsdbBt1m0RLZjjuQR5sdnrAwJGTjh-SWThAA2C2NGlLxXWWXuRBA?width=640&height=480&cropmode=none)

* Non-busy-waiting/semaphore    

|Item|1|2|3|4|5|6|7|8|9|10|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|AEVERAGE|952062.06|1404340.32|1858258.92|2318424.76|2777071.88|3240547.76|3684200.82|4175949.00|4675875.82|5166361.92|
|STDEV|202261.71|208502.52|221823.45|225574.13|233953.98|243500.53|252043.84|309197.04|434971.52|440096.43|

![Performance_analyses_semaphore_50](https://alxvxg.by.files.1drv.com/y4mH70Etzbltx0gbJ8wvScOANCrwM0u-xgRorgPXUVHU9x6Uef4Q_AFspjt3DJ1uPgANyA-CvXZHjwgljYb7IQ4czTGQlXAJ3HAt620jR0kCgBtQ1xGRb-wrxpG3f8BQgN7DX4TI5YLCz6B6PG7L_7KnYLgmnkN5tsX0Nb8FnQJ8JiYEd0JtPAj75cXtVr17lqYoh-QQDBNhNRaoLlYPZNaNA?width=908&height=504&cropmode=none)

* Busy-waiting

|Item|1|2|3|4|5|6|7|8|9|10|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|AEVERAGE|81401899.12|78595747.00|96720242.47|73802317.47|86406862.33|113321935.51|75721500.23|71811626.84|102355011.30|92631277.79|
|STDEV|80598657.30|83940348.92|106958346.35|88379818.08|106084843.00|114382633.24|102823248.70|88015500.51|100263936.56|87994272.34|

![Performance_analyses_busy-waiting_50](https://plq6ug.by.files.1drv.com/y4mNSZH81YirqAC8rsaWm1m74_UMIagf9VYS5uR3RDskHwQY8n3R6yQklKbc2imC2KrkH5VA4nCHne65NAjhSCgS8RaiLpyU2qM55QuuSlkM1dRRk7laFHrL_glUQiuj47gsXOblnQlfsZZN5awjzQGY6OeTG2khhYSNpCJKR8q4a2QlDB_nYHD8sYxdN0nyTBdlfZYCflmXSt9hEzCpVN9oA?width=640&height=480&cropmode=none)

