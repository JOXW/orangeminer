# ORANGEMINER

![image](https://github.com/JOXW/orangeminer/blob/master/orangeminer.png)

A CPU and NVIDIA miner for Securus / Argon2id .

## Download

[Go here to download the latest release.](https://github.com/JOXW/orangeminer/releases) 

If you prefer to compile yourself, read on. This can result in increased hashrates in some cases.

## Algorithms Supported
* Securus - choose `securus` or `src`

Want the miner to support another argon coin? Open an issue, or even better, open a pull request!

## Notes

* Supports AVX-512, AVX-2, SSE4.1, SSSE3, SSE2 and NEON optimizations.
* Supports NVIDIA GPUs.
* You can set a priority to a pool to determine which ones are tried first. A smaller priority number means we will connect to it first. 0 = highest priority. If we are not connected to the highest priority pool, we will continuously retry connecting to higher priority pools.

* Dev fee is 1%.
* Supports [xmrig-proxy](https://github.com/xmrig/xmrig-proxy) - Make sure to enable `"niceHash": true` in your pool config.

## Configuring

There are a couple of ways to configure the miner.

* Just start it, and walk throught the guided setup. Upon completion, the config will be written to `config.json` for modification if desired.
* Use command line options. Use `orangeminer --help` to list them all. It is not recommended to use command line options, as they are less configurable than the config. Only `--algorithm`, `--pool`, and `--username` are mandatory.

For example:
```
./orangeminer --algorithm securus --pool pool.securuscoin.org:5555 --username SCR1PahF4AN2DCBDE8MbFFTk6ABFiRe2nUNSP6gVhZANFfx2t6P5t8LKi7J2YkeaaJcR7jR4ZVKK2j88PtVmdAG18SwZKeLBUn
```

* Copy the below config to `config.json` and modify to your purposes.

```json
{
    "hardwareConfiguration": {
        "cpu": {
            "enabled": true,
            "optimizationMethod": "Auto",
            "threadCount": 12
        },
        "nvidia": {
            "devices": [
                {
                    "desktopLag": 100.0,
                    "enabled": true,
                    "id": 0,
                    "intensity": 50.0,
                    "name": "GeForce GTX 1070"
                }
            ]
        }
    },
    "pools": [
        {
            "agent": "",
            "algorithm": "securus",
            "host": "pool.securuscoin.org",
            "niceHash": false,
            "password": "x",
            "port": 5555,
            "priority": 0,
            "rigID": "",
            "ssl": false,
            "username": "SCR1PahF4AN2DCBDE8MbFFTk6ABFiRe2nUNSP6gVhZANFfx2t6P5t8LKi7J2YkeaaJcR7jR4ZVKK2j88PtVmdAG18SwZKeLBUn"
        }
    ]
}
```

### Disabling CPU/GPU/Specific Cards

* If you want to disable CPU mining, either set `enabled` to `false` in the cpu section, or start the miner with the `--disableCPU` flag.
* If you want to disable Nvidia mining, either set `enabled` to `false` for each card in the nvidia devices section, or start the miner with the `--disableNVIDIA` flag.

* If you want to disable a specific Nvidia or AMD card, just set `enabled` to `false` in the nvidia devices section for the appropriate card.

Note that changing the `name` field does not do anything. It is only there to help you identify which device has which id.
It's highly recommended that you don't change the `name` or `id` fields, or you may end up with quite a confusing result.

You can always delete your config file, and let the program regenerate it, if you mess up.

### GPU Configuration

#### Intensity

* In addition to enabling and disabling specific cards, you can also configure how many threads and how much memory they use.
* This is done by altering the `intensity` value in the config.
* A value of `100` for intensity means the maximum threads and memory will be used.
* A value of `0` for intensity means no threads and memory will be used.
* Lower intensities don't neccessarily mean lower hashrate.

#### Desktop Lag

* The `desktopLag` value determines how long we will sleep between kernel launches.
* The default value of `100` means there are no sleeps between launches.
* This is appropriate for most setups, where you are just mining.
* However, if you are mining on your personal PC, and your desktop is quite laggy while mining, you can use this setting to decrease the lags.
* A value of 100 means maximum desktop lag, a value of 0 means minimum desktop lag.
* You can see how long we will sleep between launches printed at startup.
* A lower value of desktop lag means less hashrate, because we launch the hasher kernel less.

### CPU Optimization method

By default, the program will automatically choose the optimization method to use.

In some cases, you may find you get better performance by manually specifying the optimization method to use.

You can, if desired, use a different optimization method, or disable optimizations altogether.

Note that you can only use optimizations that your hardware has support for - these are printed at startup.

Simply set the desired value in the `optimizationMethod` config field.

Available optimizations for each platform are as follows:

#### x86_64 (64 bit Intel/AMD Windows/Mac/Linux)

* `AVX-512`
* `AVX-2`
* `SSE4.1`
* `SSSE3`
* `SSE2`
* `None`
* `Auto`

#### ARMv8

Note: On ARMv8, `Auto` uses no optimizations. From my testing, the NEON implementation actually performs worse than the reference implementation. You may want to experiment with toggling between `NEON` and `None` if you are on an ARM machine.

* `NEON`
* `None`
* `Auto`

#### Anything else

* `None`
* `Auto`


