{
  "version": "1.2",
  "package": {
    "name": "",
    "version": "",
    "description": "",
    "author": "",
    "image": ""
  },
  "design": {
    "board": "iCEBreaker",
    "graph": {
      "blocks": [
        {
          "id": "c95112d2-01d4-48e2-9887-6e38114f14ee",
          "type": "basic.output",
          "data": {
            "name": "",
            "virtual": false,
            "pins": [
              {
                "index": "0",
                "name": "LED5",
                "value": "21"
              }
            ]
          },
          "position": {
            "x": 1320,
            "y": 200
          }
        },
        {
          "id": "22820305-1170-49ec-bf84-e826d05cac36",
          "type": "basic.input",
          "data": {
            "name": "CLOCK",
            "virtual": false,
            "pins": [
              {
                "index": "0",
                "name": "BTN3",
                "value": "18"
              }
            ],
            "clock": false
          },
          "position": {
            "x": -40,
            "y": 280
          }
        },
        {
          "id": "90fb2a58-44bc-446d-ad33-26926762b495",
          "type": "basic.output",
          "data": {
            "name": "",
            "virtual": false,
            "pins": [
              {
                "index": "0",
                "name": "LED1",
                "value": "26"
              }
            ]
          },
          "position": {
            "x": 1328,
            "y": 328
          }
        },
        {
          "id": "15dd11b2-2939-4701-8ed8-d808c6e167c9",
          "type": "basic.output",
          "data": {
            "name": "",
            "virtual": false,
            "pins": [
              {
                "index": "0",
                "name": "LED4",
                "value": "23"
              }
            ]
          },
          "position": {
            "x": 1328,
            "y": 456
          }
        },
        {
          "id": "c1ffba14-d589-4b08-b562-32dcf7e933e6",
          "type": "basic.input",
          "data": {
            "name": "X_INPUT",
            "virtual": false,
            "pins": [
              {
                "index": "0",
                "name": "BTN2",
                "value": "19"
              }
            ],
            "clock": false
          },
          "position": {
            "x": -64,
            "y": 456
          }
        },
        {
          "id": "b567bf2d-d9be-4be7-aefd-7b0ea1d14676",
          "type": "8026abbda6bfa79c6f4c6debd4e97ae7b51ee8d3",
          "position": {
            "x": 136,
            "y": 456
          },
          "size": {
            "width": 96,
            "height": 64
          }
        },
        {
          "id": "8f28b37d-216c-4dd2-a3fd-c56c37832ee3",
          "type": "cfd9babc26edba88e2152493023c4bef7c47f247",
          "position": {
            "x": 136,
            "y": 184
          },
          "size": {
            "width": 96,
            "height": 64
          }
        },
        {
          "id": "5992e11a-6879-4a07-8585-1564e6c4f1d6",
          "type": "8b89a54940796d87a750d07e9b511ed41621037e",
          "position": {
            "x": 392,
            "y": 200
          },
          "size": {
            "width": 96,
            "height": 64
          }
        },
        {
          "id": "4e47081d-c9a1-4806-b75e-1e0fd4199630",
          "type": "8b89a54940796d87a750d07e9b511ed41621037e",
          "position": {
            "x": 392,
            "y": 328
          },
          "size": {
            "width": 96,
            "height": 64
          }
        },
        {
          "id": "083e33e4-a5f3-45b8-a9af-998679120399",
          "type": "basic.code",
          "data": {
            "ports": {
              "in": [
                {
                  "name": "y1"
                },
                {
                  "name": "y2"
                },
                {
                  "name": "xi"
                }
              ],
              "out": [
                {
                  "name": "d1"
                },
                {
                  "name": "d2"
                },
                {
                  "name": "zo"
                }
              ]
            },
            "params": [],
            "code": "\nassign d1 = (xi&y2)|(~y2&y1);\nassign d2 = xi^y1;\nassign zo = (xi&y2&(~y1))|((~xi)&(~y2)&y1);\n\n"
          },
          "position": {
            "x": 680,
            "y": 168
          },
          "size": {
            "width": 464,
            "height": 384
          }
        }
      ],
      "wires": [
        {
          "source": {
            "block": "8f28b37d-216c-4dd2-a3fd-c56c37832ee3",
            "port": "22ff3fa1-943b-4d1a-bd89-36e1c054d077"
          },
          "target": {
            "block": "5992e11a-6879-4a07-8585-1564e6c4f1d6",
            "port": "6855f64f-fa1c-4371-b2e1-a98970674a96"
          }
        },
        {
          "source": {
            "block": "5992e11a-6879-4a07-8585-1564e6c4f1d6",
            "port": "ffdd9aa2-aea3-4aa9-8431-80e799226774"
          },
          "target": {
            "block": "083e33e4-a5f3-45b8-a9af-998679120399",
            "port": "y1"
          }
        },
        {
          "source": {
            "block": "4e47081d-c9a1-4806-b75e-1e0fd4199630",
            "port": "ffdd9aa2-aea3-4aa9-8431-80e799226774"
          },
          "target": {
            "block": "083e33e4-a5f3-45b8-a9af-998679120399",
            "port": "y2"
          }
        },
        {
          "source": {
            "block": "8f28b37d-216c-4dd2-a3fd-c56c37832ee3",
            "port": "22ff3fa1-943b-4d1a-bd89-36e1c054d077"
          },
          "target": {
            "block": "4e47081d-c9a1-4806-b75e-1e0fd4199630",
            "port": "6855f64f-fa1c-4371-b2e1-a98970674a96"
          },
          "vertices": [
            {
              "x": 336,
              "y": 272
            }
          ]
        },
        {
          "source": {
            "block": "083e33e4-a5f3-45b8-a9af-998679120399",
            "port": "d1"
          },
          "target": {
            "block": "c95112d2-01d4-48e2-9887-6e38114f14ee",
            "port": "in"
          }
        },
        {
          "source": {
            "block": "083e33e4-a5f3-45b8-a9af-998679120399",
            "port": "d1"
          },
          "target": {
            "block": "5992e11a-6879-4a07-8585-1564e6c4f1d6",
            "port": "b32a6101-5bd1-4bcf-ae5f-e569b958a6a2"
          },
          "vertices": [
            {
              "x": 1192,
              "y": 192
            },
            {
              "x": 640,
              "y": 136
            }
          ]
        },
        {
          "source": {
            "block": "083e33e4-a5f3-45b8-a9af-998679120399",
            "port": "zo"
          },
          "target": {
            "block": "15dd11b2-2939-4701-8ed8-d808c6e167c9",
            "port": "in"
          }
        },
        {
          "source": {
            "block": "083e33e4-a5f3-45b8-a9af-998679120399",
            "port": "d2"
          },
          "target": {
            "block": "90fb2a58-44bc-446d-ad33-26926762b495",
            "port": "in"
          }
        },
        {
          "source": {
            "block": "083e33e4-a5f3-45b8-a9af-998679120399",
            "port": "d2"
          },
          "target": {
            "block": "4e47081d-c9a1-4806-b75e-1e0fd4199630",
            "port": "b32a6101-5bd1-4bcf-ae5f-e569b958a6a2"
          },
          "vertices": [
            {
              "x": 352,
              "y": 280
            }
          ]
        },
        {
          "source": {
            "block": "22820305-1170-49ec-bf84-e826d05cac36",
            "port": "out"
          },
          "target": {
            "block": "8f28b37d-216c-4dd2-a3fd-c56c37832ee3",
            "port": "c9e1af2a-6f09-4cf6-a5b3-fdf7ec2c6530"
          }
        },
        {
          "source": {
            "block": "c1ffba14-d589-4b08-b562-32dcf7e933e6",
            "port": "out"
          },
          "target": {
            "block": "b567bf2d-d9be-4be7-aefd-7b0ea1d14676",
            "port": "bb4a1ca9-1b30-471e-92ca-ca7ff2fc1150"
          }
        },
        {
          "source": {
            "block": "b567bf2d-d9be-4be7-aefd-7b0ea1d14676",
            "port": "a139fa0d-9b45-4480-a251-f4a66b49aa23"
          },
          "target": {
            "block": "083e33e4-a5f3-45b8-a9af-998679120399",
            "port": "xi"
          }
        }
      ]
    }
  },
  "dependencies": {
    "8026abbda6bfa79c6f4c6debd4e97ae7b51ee8d3": {
      "package": {
        "name": "Pull-up",
        "version": "1.0.0",
        "description": "FPGA internal pull-up configuration on the connected input port",
        "author": "Juan González",
        "image": "%3Csvg%20id=%22svg2%22%20xmlns=%22http://www.w3.org/2000/svg%22%20viewBox=%22-265%20401.5%2063.5%2038.4%22%3E%3Cstyle%3E.st0%7Bdisplay:none%7D.st1%7Bfill:none;stroke:#000;stroke-width:.75;stroke-linejoin:round;stroke-miterlimit:10%7D.st2%7Bfill:#010002%7D%3C/style%3E%3Cpath%20class=%22st0%22%20d=%22M-242.5%20411.8v11.8h-5.4v-11.8h5.4m1-1h-7.4v13.8h7.4v-13.8z%22/%3E%3Cpath%20d=%22M-212%20425.6l-15.4-8.7v8.5h-17.4v-2.7c0-.2-.1-.4-.3-.4l-2.3-1.2%205.6-2.9c.2-.1.3-.3.3-.5s-.1-.4-.3-.4l-5.7-2.7%202.4-1.6c.1-.1.2-.2.2-.4v-2.7h3.1l-3.5-6.1-3.5%206.1h3v2.5l-2.9%202c-.1.1-.2.3-.2.5s.1.3.3.4l5.6%202.6-5.6%202.9c-.2.1-.3.3-.3.4s.1.4.3.4l2.9%201.5V425.5H-265v1.2h37.6v8.5l15.4-8.7h10.5v-.8H-212zm-33.3-20.4l2.2%203.9h-4.5l2.3-3.9zm19.2%2027.7v-13.8l12.3%206.9-12.3%206.9z%22/%3E%3C/svg%3E"
      },
      "design": {
        "config": "true",
        "pullup": "true",
        "graph": {
          "blocks": [
            {
              "id": "bb4a1ca9-1b30-471e-92ca-ca7ff2fc1150",
              "type": "basic.input",
              "data": {
                "name": ""
              },
              "position": {
                "x": 64,
                "y": 200
              }
            },
            {
              "id": "a139fa0d-9b45-4480-a251-f4a66b49aa23",
              "type": "basic.output",
              "data": {
                "name": ""
              },
              "position": {
                "x": 760,
                "y": 200
              }
            },
            {
              "id": "2b245a71-2d80-466b-955f-e3d61839fe25",
              "type": "basic.code",
              "data": {
                "code": "// Pull up\n\nwire din, dout, outen;\n\nassign o = din;\n\nSB_IO #(\n    .PIN_TYPE(6'b 1010_01),\n    .PULLUP(1'b 1)\n) io_pin (\n    .PACKAGE_PIN(i),\n    .OUTPUT_ENABLE(outen),\n    .D_OUT_0(dout),\n    .D_IN_0(din)\n);",
                "params": [],
                "ports": {
                  "in": [
                    {
                      "name": "i"
                    }
                  ],
                  "out": [
                    {
                      "name": "o"
                    }
                  ]
                }
              },
              "position": {
                "x": 256,
                "y": 104
              },
              "size": {
                "width": 384,
                "height": 256
              }
            }
          ],
          "wires": [
            {
              "source": {
                "block": "bb4a1ca9-1b30-471e-92ca-ca7ff2fc1150",
                "port": "out"
              },
              "target": {
                "block": "2b245a71-2d80-466b-955f-e3d61839fe25",
                "port": "i"
              }
            },
            {
              "source": {
                "block": "2b245a71-2d80-466b-955f-e3d61839fe25",
                "port": "o"
              },
              "target": {
                "block": "a139fa0d-9b45-4480-a251-f4a66b49aa23",
                "port": "in"
              }
            }
          ]
        }
      }
    },
    "cfd9babc26edba88e2152493023c4bef7c47f247": {
      "package": {
        "name": "Debouncer",
        "version": "1.0.0",
        "description": "Remove the rebound on a mechanical switch",
        "author": "Juan González",
        "image": "%3Csvg%20xmlns=%22http://www.w3.org/2000/svg%22%20viewBox=%22-252%20400.9%2090%2040%22%3E%3Cpath%20d=%22M-251.547%20436.672h22.802v-30.353h5.862v30.353h5.259v-30.353h3.447v30.353h2.984v-30.353h3.506v30.523h6.406V405.77h38.868%22%20fill=%22none%22%20stroke=%22#000%22%20stroke-width=%221.4%22%20stroke-linecap=%22round%22%20stroke-linejoin=%22round%22/%3E%3Cpath%20d=%22M-232.57%20403.877l26.946%2032.391M-205.624%20403.877l-26.946%2032.391%22%20fill=%22none%22%20stroke=%22red%22%20stroke-width=%223%22%20stroke-linecap=%22round%22/%3E%3C/svg%3E"
      },
      "design": {
        "graph": {
          "blocks": [
            {
              "id": "4bf41c17-a2da-4140-95f7-2a80d51b1e1a",
              "type": "basic.input",
              "data": {
                "name": "",
                "clock": true
              },
              "position": {
                "x": 48,
                "y": 144
              }
            },
            {
              "id": "22ff3fa1-943b-4d1a-bd89-36e1c054d077",
              "type": "basic.output",
              "data": {
                "name": ""
              },
              "position": {
                "x": 768,
                "y": 208
              }
            },
            {
              "id": "c9e1af2a-6f09-4cf6-a5b3-fdf7ec2c6530",
              "type": "basic.input",
              "data": {
                "name": "",
                "clock": false
              },
              "position": {
                "x": 48,
                "y": 272
              }
            },
            {
              "id": "92490e7e-c3ba-4e9c-a917-2a771d99f1ef",
              "type": "basic.code",
              "data": {
                "code": "//-- Debouncer Circuit\n//-- It produces a stable output when the\n//-- input signal is bouncing\n\nreg btn_prev = 0;\nreg btn_out_r = 0;\n\nreg [16:0] counter = 0;\n\n\nalways @(posedge clk) begin\n\n  //-- If btn_prev and btn_in are differents\n  if (btn_prev ^ in == 1'b1) begin\n    \n      //-- Reset the counter\n      counter <= 0;\n      \n      //-- Capture the button status\n      btn_prev <= in;\n  end\n    \n  //-- If no timeout, increase the counter\n  else if (counter[16] == 1'b0)\n      counter <= counter + 1;\n      \n  else\n    //-- Set the output to the stable value\n    btn_out_r <= btn_prev;\n\nend\n\nassign out = btn_out_r;\n",
                "params": [],
                "ports": {
                  "in": [
                    {
                      "name": "clk"
                    },
                    {
                      "name": "in"
                    }
                  ],
                  "out": [
                    {
                      "name": "out"
                    }
                  ]
                }
              },
              "position": {
                "x": 264,
                "y": 112
              },
              "size": {
                "width": 384,
                "height": 256
              }
            }
          ],
          "wires": [
            {
              "source": {
                "block": "92490e7e-c3ba-4e9c-a917-2a771d99f1ef",
                "port": "out"
              },
              "target": {
                "block": "22ff3fa1-943b-4d1a-bd89-36e1c054d077",
                "port": "in"
              }
            },
            {
              "source": {
                "block": "4bf41c17-a2da-4140-95f7-2a80d51b1e1a",
                "port": "out"
              },
              "target": {
                "block": "92490e7e-c3ba-4e9c-a917-2a771d99f1ef",
                "port": "clk"
              }
            },
            {
              "source": {
                "block": "c9e1af2a-6f09-4cf6-a5b3-fdf7ec2c6530",
                "port": "out"
              },
              "target": {
                "block": "92490e7e-c3ba-4e9c-a917-2a771d99f1ef",
                "port": "in"
              }
            }
          ]
        }
      }
    },
    "8b89a54940796d87a750d07e9b511ed41621037e": {
      "package": {
        "name": "Flip-flop D",
        "version": "1.0.0",
        "description": "Delay flip-flop",
        "author": "Carlos Diaz",
        "image": "%3Csvg%20xmlns=%22http://www.w3.org/2000/svg%22%20viewBox=%22-252%20400.9%2090%2040%22%3E%3Ctext%20style=%22line-height:125%25%22%20x=%22-231.121%22%20y=%22429.867%22%20font-weight=%22400%22%20font-size=%2224.601%22%20font-family=%22sans-serif%22%20letter-spacing=%220%22%20word-spacing=%220%22%3E%3Ctspan%20x=%22-231.121%22%20y=%22429.867%22%3EDFF%3C/tspan%3E%3C/text%3E%3C/svg%3E"
      },
      "design": {
        "graph": {
          "blocks": [
            {
              "id": "6855f64f-fa1c-4371-b2e1-a98970674a96",
              "type": "basic.input",
              "data": {
                "name": "",
                "clock": true
              },
              "position": {
                "x": 232,
                "y": 168
              }
            },
            {
              "id": "ffdd9aa2-aea3-4aa9-8431-80e799226774",
              "type": "basic.output",
              "data": {
                "name": ""
              },
              "position": {
                "x": 864,
                "y": 232
              }
            },
            {
              "id": "b32a6101-5bd1-4bcf-ae5f-e569b958a6a2",
              "type": "basic.input",
              "data": {
                "name": "",
                "clock": false
              },
              "position": {
                "x": 232,
                "y": 304
              }
            },
            {
              "id": "e5222a6e-4717-4f08-99d7-7cde897060ca",
              "type": "basic.code",
              "data": {
                "code": "// D flip-flop\n\nreg q = 1'b0;\n\nalways @(posedge clk)\nbegin\n  q <= d;\nend\n\n",
                "params": [],
                "ports": {
                  "in": [
                    {
                      "name": "clk"
                    },
                    {
                      "name": "d"
                    }
                  ],
                  "out": [
                    {
                      "name": "q"
                    }
                  ]
                }
              },
              "position": {
                "x": 432,
                "y": 128
              },
              "size": {
                "width": 368,
                "height": 272
              }
            }
          ],
          "wires": [
            {
              "source": {
                "block": "b32a6101-5bd1-4bcf-ae5f-e569b958a6a2",
                "port": "out"
              },
              "target": {
                "block": "e5222a6e-4717-4f08-99d7-7cde897060ca",
                "port": "d"
              }
            },
            {
              "source": {
                "block": "6855f64f-fa1c-4371-b2e1-a98970674a96",
                "port": "out"
              },
              "target": {
                "block": "e5222a6e-4717-4f08-99d7-7cde897060ca",
                "port": "clk"
              }
            },
            {
              "source": {
                "block": "e5222a6e-4717-4f08-99d7-7cde897060ca",
                "port": "q"
              },
              "target": {
                "block": "ffdd9aa2-aea3-4aa9-8431-80e799226774",
                "port": "in"
              }
            }
          ]
        }
      }
    }
  }
}