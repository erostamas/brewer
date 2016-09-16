<html>
<body>

<iframe name="devnull" style="display:none;"></iframe>
<form action="index.php" method="get" target="devnull">
Command: <input type="text" name="command"><br>
<input type="submit"><br>
</form>

Current Temperature:     <span id="temp"></span><br>
Setpoint:                <span id="setpoint"></span><br>
Delta:                   <span id="delta"></span><br>
Current mode:            <span id="mode"></span><br>
<span id="timetonextsegment"></span><br>

<script type="text/javascript" src="js/fusioncharts.js"></script>
<script type="text/javascript" src="js/themes/fusioncharts.theme.fint.js?cacheBust=56"></script>
<script>


</script>

<script type="text/javascript">
  FusionCharts.ready(function(){
    var tempChart = new FusionCharts({
    type: 'thermometer',
    renderAt: 'current_temp_chart_container',
    id: 'current_temp_chart',
    width: '240',
    height: '310',
    dataFormat: 'json',
    dataSource: {
        "chart": {
            "caption": "Current Temperature",
            "subcaption": "",
            "lowerLimit": "0",
            "upperLimit": "100",
            "decimals": "1",
            "numberSuffix": "°C",
            "showhovereffect": "0",
            "thmFillColor": "#008ee4",
            "showGaugeBorder": "1",
            "gaugeBorderColor": "#008ee4",
            "gaugeBorderThickness": "2",
            "gaugeBorderAlpha": "30",
            "thmOriginX": "100",
            "chartBottomMargin": "20",
            "valueFontColor": "#000000",
            "valueFontSize": "35",
            "theme": "fint",
            "autoScale": "0"
        },
        "value": "0",
    },
    "events": {
        "initialized": function(evt, arg) {
            updateColor = function(evtObj, argObj) {};
        },
        'renderComplete': function(evt, arg) {
            updateColor(evt, arg);
        },
        'realtimeUpdateComplete': function(evt, arg) {
            updateColor(evt, arg);
        },
        'disposed': function(evt, arg) {
            clearInterval(evt.sender.dataUpdate);
        }
    }
}
);

var setpointChart = new FusionCharts({
    type: 'thermometer',
    renderAt: 'setpoint_chart_container',
    id: 'setpoint_chart',
    width: '240',
    height: '310',
    dataFormat: 'json',
    dataSource: {
        "chart": {
            "caption": "Setpoint",
            "subcaption": "",
            "lowerLimit": "0",
            "upperLimit": "100",

            "decimals": "1",
            "numberSuffix": "°C",
            "showhovereffect": "0",
            "thmFillColor": "#008ee4",
            "showGaugeBorder": "1",
            "gaugeBorderColor": "#008ee4",
            "gaugeBorderThickness": "2",
            "gaugeBorderAlpha": "30",
            "thmOriginX": "100",
            "chartBottomMargin": "20",
            "valueFontColor": "#000000",
            "valueFontSize": "35",
            "theme": "fint"
        },
        "value": "0"
    },
    "events": {
        "initialized": function(evt, arg) {
            updateAnnotation = function(evtObj, argObj) {};
        },
        'renderComplete': function(evt, arg) {
            updateAnnotation(evt, arg);
        },
        'realtimeUpdateComplete': function(evt, arg) {
            updateAnnotation(evt, arg);
        },
        'disposed': function(evt, arg) {
            clearInterval(evt.sender.dataUpdate);
        }
    }
}
);

var outputChart = new FusionCharts({
    type: 'hled',
    renderAt: 'output_chart_container',
    id: 'output_chart',
    width: '450',
    height: '220',
    dataFormat: 'json',
    dataSource: {
        "chart": {
            "caption": "Output",
            "subcaption": "",
            "lowerLimit": "0",
            "upperLimit": "100",

            "decimals": "1",
            "numberSuffix": "%",
            "showhovereffect": "0",
            "thmFillColor": "#008ee4",
            "showGaugeBorder": "1",
            "gaugeBorderColor": "#008ee4",
            "gaugeBorderThickness": "2",
            "gaugeBorderAlpha": "30",
            "thmOriginX": "100",
            "chartBottomMargin": "20",
            "valueFontColor": "#000000",
            "valueFontSize": "35",
            "theme": "fint"
        },
        "colorRange": {
            "color": [{
                "minValue": "0",
                "maxValue": "45",
                "code": "#6baa01"
            }, {
                "minValue": "45",
                "maxValue": "75",
                "code": "#f8bd19"
            }, {
                "minValue": "75",
                "maxValue": "100",
                "code": "#e44a00"
            }]
        },
        "value": "0"
    },
    "events": {
        "initialized": function(evt, arg) {
            updateAnnotation = function(evtObj, argObj) {};
        },
        'renderComplete': function(evt, arg) {
            updateAnnotation(evt, arg);
        },
        'realtimeUpdateComplete': function(evt, arg) {
            updateAnnotation(evt, arg);
        },
        'disposed': function(evt, arg) {
            clearInterval(evt.sender.dataUpdate);
        }
    }
}
);

tempChart.render();
setpointChart.render();
outputChart.render();

});

function refresh() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "data.xml", true);
    xhttp.responseType = 'document';
    xhttp.overrideMimeType('text/xml');
    
    xhttp.onload = function () {
        if (xhttp.readyState == xhttp.DONE && xhttp.status == 200) {
            xmlDoc = xhttp.responseXML;
            document.getElementById("temp").innerHTML = parseFloat(xmlDoc.getElementsByTagName("temp")[0].childNodes[0].nodeValue);
            document.getElementById("setpoint").innerHTML = parseFloat(xmlDoc.getElementsByTagName("setpoint")[0].childNodes[0].nodeValue);
            document.getElementById("delta").innerHTML = parseFloat(xmlDoc.getElementsByTagName("delta")[0].childNodes[0].nodeValue);
            document.getElementById("mode").innerHTML = xmlDoc.getElementsByTagName("mode")[0].childNodes[0].nodeValue;
            if (xmlDoc.getElementsByTagName("mode")[0].childNodes[0].nodeValue == "AUTO") {
                document.getElementById("timetonextsegment").innerHTML = "Time to next segment: " + xmlDoc.getElementsByTagName("timetonextsegment")[0].childNodes[0].nodeValue;
            }
            
            var tempChartRef = FusionCharts("current_temp_chart");
            //tempChartRef.setChartAttribute("valueFontColor","#6baa01");
            tempChartRef.setData(xmlDoc.getElementsByTagName("temp")[0].childNodes[0].nodeValue);
            var setpointChartRef = FusionCharts("setpoint_chart");
            setpointChartRef.setData(xmlDoc.getElementsByTagName("setpoint")[0].childNodes[0].nodeValue);
            var outputChartRef = FusionCharts("output_chart");
            outputChartRef.setData(xmlDoc.getElementsByTagName("output")[0].childNodes[0].nodeValue);
        }
    }
    xhttp.send();
    
    setTimeout(refresh, 1000);
}

refresh();
</script>
  <span id="current_temp_chart_container">FusionCharts XT will load here!</span>
  <span id="setpoint_chart_container">FusionCharts XT will load here!</span><br>
  <div id="output_chart_container">FusionCharts XT will load here!</div><br>
</body>
</html>

<?php
function send_command()
{
    $sock = stream_socket_client('unix:///var/run/brewer/brewer_socket_file', $errno, $errstr);
    if (!$sock) {
        echo "$errstr ($errno)<br />\n";
    } else {
        fwrite($sock, $_GET["command"]);

        fclose($sock);
        echo "last command: ".$_GET["command"];
    }
}
send_command();
?>