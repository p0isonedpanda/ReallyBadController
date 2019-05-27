<?php
    // show any errors
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);

    include 'dbconnect.php';

    $query = 'SELECT * FROM inputs';
    $result = $conn->query($query)->fetch_assoc();

    echo '<div class="row">';
    if ($result['usonic'] == 1) {
    echo '    <div class="col"><p>usonic: active</p></div>';
    } else {
    echo '    <div class="col"><p>usonic: not active</p></div>';
    }
    echo '    <div class="col"><p>ldr: ' . floor($result['ldr'] / 1024 * 100) . '%</p></div>';
    echo '    <div class="col"><p>temp: ' . floor($result['temp'] / 1024 * 100) . '%</p></div>';
    echo '</div>';

    echo '<div class="row">';
    echo '    <div class="col">';
    echo '        <p>joyx: ' . $result['joyx'] . '</p>';
    echo '        <p>joyy: ' . $result['joyy'] . '</p>';
    echo '    </div>';
    if ($result['button'] == 1) {
    echo '    <div class="col" style="padding: auto;"><p>button: pressed</p></div>';
    } else {
    echo '    <div class="col" style="padding: auto;"><p>button: not pressed</p></div>';
    }
    echo '</div>';

    $conn->close();
?>
