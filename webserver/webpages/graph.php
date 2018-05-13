<html>
<head>
  <link rel="stylesheet" type="text/css" href="http://fonts.googleapis.com/css?family=Tangerine&amp;v1" />
  <link rel="stylesheet" type="text/css" href="http://fonts.googleapis.com/css?family=Yanone+Kaffeesatz" />
  <link rel="stylesheet" type="text/css" href="style/style.css" />
</head>

<script src="Moments.js" type="text/javascript"></script>
<script src="Chart.js" type="text/javascript"></script>

<?php
    $hst_file = 'unknown';
    $ts = 0;
    if(isset($_GET['hst_file'])){
        $hst_file = $_GET['hst_file']; //some_value
    }
    if(isset($_GET['ts'])){
        $ts = $_GET['ts']; //some_value
    }
    echo '<hst_file>' . $hst_file . '</hst_file>'
?>

<canvas id="myChart" width="1000" height="500"></canvas>
<script>
    var ctx = document.getElementById("myChart").getContext('2d');
    
    var myElement = document.getElementsByTagName("hst_file")[0];
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "historical_data/<?php echo $hst_file;?>", true);

    xhttp.onload = function () {
        if (xhttp.readyState == xhttp.DONE && xhttp.status == 200) {
            var lines = xhttp.responseText.split("\n");
            var temp = lines[0].split(";");
            var setpoint = lines[1].split(";");
            var seconds = [];

            for (var i = <?php echo $ts;?>; i <= <?php echo $ts;?> + temp.length; i++) {
                seconds.push(new Date(i * 1000));
            }
            var myChart = new Chart(ctx, {
                            type: 'line',
                            data: {
                                labels: seconds,
                                datasets: [{
                                    label: "Temperature",
                                    backgroundColor: 'rgb(100, 100, 100)',
                                    borderColor: 'rgb(255, 0, 0)',
                                    data: temp,
                                    fill: false
                                },
                                {
                                    label: "Setpoint",
                                    backgroundColor: 'rgb(100, 100, 100)',
                                    borderColor: 'rgb(255, 255, 0)',
                                    data: setpoint,
                                    fill: false
                                }]
                            },
                            options: {
                                responsive: false,
                                scales: {
                                    yAxes: [{
                                        gridLines: {
                                            color: 'white',
                                            lineWidth: 1
                                        },
                                        ticks: {
                                            beginAtZero:true,
                                            fontColor: "white"
                                        }
                                    }],
                                    xAxes: [{
                                        type: "time",
                                        time: {
                                            displayFormats: {
                                            'millisecond': 'hh:mm',
                                            'second': 'hh:mm',
                                            'minute': 'hh:mm',
                                            'hour': 'hh:mm',
                                            'day': 'hh:mm',
                                            'week': 'hh:mm',
                                            'month': 'hh:mm',
                                            'quarter': 'hh:mm',
                                            'year': 'hh:mm',
                                            }
                                        },
                                        display: true,
                                        scaleLabel: {
                                            display: true,
                                            labelString: 'Date'
                                        },
                                        ticks: {
                                            fontColor: 'white'
                                        }
                                    }]
                                }
                            }
            });
            //myChart.resize();
            //myChart.data.datasets[0].data.push(points);
            //myChart.update();
        }
    }
    xhttp.send();
</script>
</html>