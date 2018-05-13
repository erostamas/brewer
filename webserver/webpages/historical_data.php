<!DOCTYPE HTML>
<html>

<head>
  <title>Brewer</title>
  <meta name="description" content="website description" />
  <meta name="keywords" content="website keywords, website keywords" />
  <meta http-equiv="content-type" content="text/html; charset=windows-1252" />
  <link rel="stylesheet" type="text/css" href="http://fonts.googleapis.com/css?family=Tangerine&amp;v1" />
  <link rel="stylesheet" type="text/css" href="http://fonts.googleapis.com/css?family=Yanone+Kaffeesatz" />
  <link rel="stylesheet" type="text/css" href="style/style.css" />
</head>

<body>
  <div id="main">
    <div id="header">
      <div id="logo">
        <h1>Brewer</h1>
        <div class="slogan">Kösz, hogy hivtál Csu</div>
      </div>
      <div id="menubar">
        <ul id="menu">
          <!-- put class="current" in the li tag for the selected page - to highlight which page you're on -->
          <li><a href="index.html">Home</a></li>
          <li class="current"><a href="historical_data.php">Historical data</a></li>
        </ul>
      </div>
    </div>
    <div id="site_content">
      <div id="content">
        <table style="width:100%">
          <tr>
            <th>Name</th>
            <th>Date</th>
          </tr>
        <?php
          if ($handle = opendir('./historical_data')) {
              while (false !== ($entry = readdir($handle))) {
                  if ($entry != "." && $entry != "..") {
                      if (preg_match('/(.*)_([0-9]+)\.hst/', $entry, $matches)) {
                          echo '<tr>';
                          echo '<td><a href="graph.php?hst_file=' . $entry . '&ts=' . $matches[2] . '">' . $matches[1] . '</a></td>';
                          echo '<td>' . date("Y M d H:i:s", $matches[2]) . '</td>';
                          echo '</tr>';
                      }
                  }
              }
              closedir($handle);
          }
        ?>
        </table>
      </div>
    </div>
    <div id="footer">
      <p>Copyright &copy; simplestyle_8 | <a href="http://validator.w3.org/check?uri=referer">HTML5</a> | <a href="http://jigsaw.w3.org/css-validator/check/referer">CSS</a> | <a href="http://www.html5webtemplates.co.uk">design from HTML5webtemplates.co.uk</a></p>
    </div>
  </div>
</body>
</html>
