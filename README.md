# ModularDeviceBase

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

## Ancestors

[ModularServer](https://github.com/janelia-arduino/ModularServer)

## Clients

## Devices

[modular_device_base](https://github.com/janelia-modular-devices/modular_device_base.git)

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["ModularDeviceBase"],
    "functions":[
      "forwardToAddress"
    ],
    "parameters":[
      "address",
      "request"
    ],
    "properties":[],
    "callbacks":[]
  }
}
```

## API Verbose

```json
{
  "id":"getApiVerbose",
  "result":{
    "firmware":["ModularDeviceBase"],
    "functions":[
      {
        "name":"forwardToAddress",
        "parameters":[
          "address",
          "request"
        ],
        "result_type":"object"
      },
      {
        "name":"getClientInfo",
        "parameters":[],
        "result_type":"object"
      }
    ],
    "parameters":[
      {
        "name":"address",
        "type":"array"
      },
      {
        "name":"request",
        "type":"array"
      }
    ],
    "properties":[],
    "callbacks":[]
  }
}
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
