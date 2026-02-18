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
          "id": "7b866dcf-078b-4789-9153-d235b962990b",
          "type": "basic.output",
          "data": {
            "name": "PMOD",
            "virtual": false,
            "range": "[6:0]",
            "pins": [
              {
                "index": "6",
                "name": "P1_B1",
                "value": "43"
              },
              {
                "index": "5",
                "name": "P1_B2",
                "value": "38"
              },
              {
                "index": "4",
                "name": "P1_B3",
                "value": "34"
              },
              {
                "index": "3",
                "name": "P1_B4",
                "value": "31"
              },
              {
                "index": "2",
                "name": "P1_B7",
                "value": "42"
              },
              {
                "index": "1",
                "name": "P1_B8",
                "value": "36"
              },
              {
                "index": "0",
                "name": "P1_B9",
                "value": "32"
              }
            ]
          },
          "position": {
            "x": 952,
            "y": 64
          }
        },
        {
          "id": "32aca53c-5184-4696-be71-febe0442a364",
          "type": "basic.input",
          "data": {
            "name": "",
            "virtual": false,
            "pins": [
              {
                "index": "0",
                "name": "CLK",
                "value": "35"
              }
            ],
            "clock": false
          },
          "position": {
            "x": 56,
            "y": 288
          }
        },
        {
          "id": "b4a378ba-7ebf-40e5-a724-acbe762544c2",
          "type": "basic.output",
          "data": {
            "name": "P",
            "virtual": false,
            "range": "[3:0]",
            "pins": [
              {
                "index": "3",
                "name": "P1_A1",
                "value": "4"
              },
              {
                "index": "2",
                "name": "P1_A2",
                "value": "2"
              },
              {
                "index": "1",
                "name": "P1_A3",
                "value": "47"
              },
              {
                "index": "0",
                "name": "P1_A4",
                "value": "45"
              }
            ]
          },
          "position": {
            "x": 952,
            "y": 392
          }
        },
        {
          "id": "3c9ddf44-9ae3-4980-8af2-4aa97af81ced",
          "type": "basic.code",
          "data": {
            "ports": {
              "in": [
                {
                  "name": "clk_i"
                }
              ],
              "out": [
                {
                  "name": "Seg",
                  "range": "[6:0]",
                  "size": 7
                },
                {
                  "name": "Dig",
                  "range": "[3:0]",
                  "size": 4
                }
              ]
            },
            "params": [],
            "code": "reg rQ2H , rQ2K;\r\nreg [27:0] CounterH,CounterK;\r\nparameter fin = 12_000_000;\r\nparameter foutH = 10;\r\nparameter foutK = 2_000;\r\nparameter CoustH = fin/(2*foutH);\r\nparameter CoustK = fin/(2*foutK);\r\n\r\nalways@(posedge clk_i) begin\r\n    CounterH <= CounterH + 1;\r\n    if(CounterH == CoustH) begin\r\n        CounterH <= 0;\r\n        rQ2H <= ~rQ2H;\r\n    end\r\n    CounterK <= CounterK + 1;\r\n    if(CounterK == CoustK) begin\r\n        CounterK <= 0;\r\n        rQ2K <= ~rQ2K;\r\n    end\r\nend\r\n\r\n//================================//\r\nreg[1:0] dispSel; //2 bit reg for display select\r\nreg[3:0] rw,rs,ru,rt;\r\nalways@(posedge rQ2K)\r\n    dispSel <= dispSel+1;\r\nalways@(posedge rQ2H) begin\r\n    rt <= (rt < 9) ? rt  + 1 : 'b0;\r\n    ru <= (rt < 9) ? ru :\r\n          (ru < 9) ? (ru + 1) : 'b0;\r\n    rs <= (rt < 9) ? rs :\r\n          (ru < 9) ? rs :\r\n          (rs < 9) ? (rs + 1) : 'b0;\r\n    rw <= (rt < 9) ? rw :\r\n          (ru < 9) ? rw :\r\n          (rs < 9) ? rw :\r\n          (rw < 9) ? (rw + 1) : 'b0;\r\nend\r\n//=================================//\r\nreg[3:0] DataOut;\r\nalways@(*)\r\n    DataOut <= (dispSel == 0) ? rt :\r\n               (dispSel == 1) ? ru :\r\n               (dispSel == 2) ? rs : rw ;\r\n//==================================//\r\nassign Dig \r\n    = (dispSel == 0) ? ~4'b0111 :\r\n     (dispSel == 1) ? ~4'b1011 :\r\n     (dispSel == 2) ? ~4'b1101 : ~4'b1110;\r\n    \r\nassign Seg\r\n    =   (DataOut==4'b0000) ? ~7'h7E :\r\n        (DataOut==4'b0001) ? ~7'h30 :\r\n        (DataOut==4'b0010) ? ~7'h6D :\r\n        (DataOut==4'b0011) ? ~7'h79 :\r\n        (DataOut==4'b0100) ? ~7'h33 :\r\n        (DataOut==4'b0101) ? ~7'h5B :\r\n        (DataOut==4'b0110) ? ~7'h5F :\r\n        (DataOut==4'b0111) ? ~7'h70 :\r\n        (DataOut==4'b1000) ? ~7'h7F :\r\n        (DataOut==4'b1001) ? ~7'h7B :\r\n        (DataOut==4'b1010) ? ~7'h77 :\r\n        (DataOut==4'b1011) ? ~7'h1F :\r\n        (DataOut==4'b1100) ? ~7'h4E :\r\n        (DataOut==4'b1101) ? ~7'h3D :\r\n        (DataOut==4'b1110) ? ~7'h4F :\r\n        (DataOut==4'b1111) ? ~7'h47 : ~7'h00;"
          },
          "position": {
            "x": 272,
            "y": 64
          },
          "size": {
            "width": 576,
            "height": 504
          }
        }
      ],
      "wires": [
        {
          "source": {
            "block": "32aca53c-5184-4696-be71-febe0442a364",
            "port": "out"
          },
          "target": {
            "block": "3c9ddf44-9ae3-4980-8af2-4aa97af81ced",
            "port": "clk_i"
          }
        },
        {
          "source": {
            "block": "3c9ddf44-9ae3-4980-8af2-4aa97af81ced",
            "port": "Seg"
          },
          "target": {
            "block": "7b866dcf-078b-4789-9153-d235b962990b",
            "port": "in"
          },
          "size": 7
        },
        {
          "source": {
            "block": "3c9ddf44-9ae3-4980-8af2-4aa97af81ced",
            "port": "Dig"
          },
          "target": {
            "block": "b4a378ba-7ebf-40e5-a724-acbe762544c2",
            "port": "in"
          },
          "size": 4
        }
      ]
    }
  },
  "dependencies": {}
}