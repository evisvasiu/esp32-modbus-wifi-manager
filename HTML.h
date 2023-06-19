const char INDEX_HTML[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>

<head>
    <title>iDispaly Navigator</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" charset="UTF-8" />
    <style>
        body {
            background-color: #dad6eb;
            font-family: Arial, Helvetica, Sans-Serif;
            Color: #000000;
            text-align: center;
        }

        }

        td {
            border: 0px solid black;
            padding: 10px;
        }

        div {
            width: 300px;
            margin: auto;
            border: 3px solid #4287f5;
        }
    </style>
</head>

<body>
    <div>
        <h3>Board configuration</h3>
        <form action="/" method="post">
            <table>
                <tr>
                    <td><label>SSID:&nbsp;</label></td>
                    <td><input maxlength="30" name="ssid"></td>
                </tr>
                <tr>
                    <td><label>Password:&nbsp;&nbsp;</label></td>
                    <td><input maxlength="30" name="password">
                </tr>
                <tr>
                    <td><label>IP:&nbsp;</label></td>
                    <td><input maxlength="30" name="ip"></td>
                </tr>
                <tr>
                    <td><label>Gateway:&nbsp;</label></td>
                    <td><input maxlength="30" name="gateway"></td>
                </tr>
                <label for="pin0">&nbsp&nbsp0:</label>
                <select name="pin0" id="pin0"style="width: 100px;">
                    <option value="5">Unused</option>                    
                    <option value="0">Digital Input</option>
                </select> &nbsp
                <label for="pin12">12:</label>
                <select name="pin12" id="pin12"style="width: 100px;">
                    <option value="5">Unused</option>                     
                    <option value="1">Digital Output</option>                 
                </select>
                <br>
                <label for="pin2">&nbsp&nbsp2:</label>
                <select name="pin2" id="pin2"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="1">Digital Output</option>
                </select> &nbsp
                <label for="pin13">13:</label>
                <select name="pin13" id="pin13"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="4">PWM</option> 
                </select>
                <br>
                <label for="pin4">&nbsp&nbsp4:</label>
                <select name="pin4" id="pin4"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="4">PWM</option>               
                </select> &nbsp
                <label for="pin14">14:</label>
                <select name="pin14" id="pin14"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                </select>
                <br>
                <label for="pin16">16:</label>
                <select name="pin16" id="pin16"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                </select> &nbsp
                <label for="pin25">25:</label>
                <select name="pin25" id="pin25"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="3">Analog Output</option>                
                </select>
                <br>
                <label for="pin17">17:</label>
                <select name="pin17" id="pin17"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                </select> &nbsp
                <label for="pin26">26:</label>
                <select name="pin26" id="pin26"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="3">Analog Output</option>  
                </select>
                <br>
                <label for="pin18">18:</label>
                <select name="pin18" id="pin18"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="4">PWM</option> 
                </select> &nbsp
                <label for="pin27">27:</label>
                <select name="pin27" id="pin27"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="4">PWM</option>       
                </select>
                <br>
                <label for="pin19">19:</label>
                <select name="pin19" id="pin19"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="4">PWM</option> 
                </select> &nbsp
                <label for="pin32">32:</label>
                <select name="pin32" id="pin32"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="2">Analog Input</option>
                    <option value="4">PWM</option>                  
                </select>
                <br>
                <label for="pin23">23:</label>
                <select name="pin23" id="pin23"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="4">PWM</option> 
                </select> &nbsp
                <label for="pin33">33:</label>
                <select name="pin33" id="pin33"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="0">Digital Input</option>
                    <option value="1">Digital Output</option>
                    <option value="2">Analog Input</option>
                    <option value="4">PWM</option>
                </select>
                <br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 
                <label for="pin34">34:</label>
                <select name="pin34" id="pin34"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="2">Analog Input</option>                  
                    <option value="0">Digital Input</option>
                </select>
                <br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 
                <label for="pin35">35:</label>
                <select name="pin35" id="pin35"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="2">Analog Input</option>                  
                    <option value="0">Digital Input</option>
                </select>
                <br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 
                <label for="pin36" >36:</label>
                <select name="pin36" id="pin36"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="2">Analog Input</option>                  
                    <option value="0">Digital Input</option>
                </select>
 
                   <br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 
                <label for="pin39">39:</label>
                <select name="pin39" id="pin39"style="width: 100px;">
                    <option value="5">Unused</option> 
                    <option value="2">Analog Input</option>                  
                    <option value="0">Digital Input</option>
                </select>
                <br><br> 
            </table>
            <input type="submit" value="Save">
        </form>
    </div>
</body>

</html>
)=====";