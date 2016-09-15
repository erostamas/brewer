<html>
<body>

<?php
function send_command()
{
    $sock = stream_socket_client('unix:///var/run/brewer/brewer_socket_file', $errno, $errstr);
    if (!$sock) {
        echo "$errstr ($errno)<br />\n";
    } else {
        fwrite($sock, $_POST["command"]);

        fclose($sock);
        echo "last command: ".$_POST["command"];
    }
}
send_command();
?>

<form action="index.php" method="post">
Command: <input type="text" name="command"><br>
<input type="submit"><br>
</form>

Current Temperature:     <span id="temp"></span><br>
Setpoint:                <span id="setpoint"></span><br>
Delta:                   <span id="delta"></span><br>
Current mode:            <span id="mode"></span><br>
<span id="timetonextsegment"></span><br>

<script>

function refresh() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "data.xml", true);
xhttp.responseType = 'document';
xhttp.overrideMimeType('text/xml');

xhttp.onload = function () {
    if (xhttp.readyState == xhttp.DONE && xhttp.status == 200) {
        xmlDoc = xhttp.responseXML;
        document.getElementById("temp").innerHTML = xmlDoc.getElementsByTagName("temp")[0].childNodes[0].nodeValue;
        document.getElementById("setpoint").innerHTML = xmlDoc.getElementsByTagName("setpoint")[0].childNodes[0].nodeValue;
        document.getElementById("delta").innerHTML = xmlDoc.getElementsByTagName("delta")[0].childNodes[0].nodeValue;
        document.getElementById("mode").innerHTML = xmlDoc.getElementsByTagName("mode")[0].childNodes[0].nodeValue;
        if (xmlDoc.getElementsByTagName("mode")[0].childNodes[0].nodeValue == "AUTO") {
            document.getElementById("timetonextsegment").innerHTML = "Time to next segment: " + xmlDoc.getElementsByTagName("timetonextsegment")[0].childNodes[0].nodeValue;
        }
    }
}
xhttp.send();

setTimeout(refresh, 1000);
}

refresh();
</script>

</body>
</html>
