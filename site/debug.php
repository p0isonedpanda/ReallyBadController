<?php
    // show any errors
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);

    include 'dbconnect.php';

    $query = 'SELECT * FROM inputs';
    $result = $conn->query($query)->fetch_assoc();

    echo '<p>usonic: ' . $result['usonic'] . '</p>';
    echo '<p>ldr: ' . $result['ldr'] . '</p>';
    echo '<p>temp: ' . $result['temp'] . '</p>';
    echo '<p>joyx: ' . $result['joyx'] . '</p>';
    echo '<p>joyy: ' . $result['joyy'] . '</p>';
    echo '<p>button: ' . $result['button'] . '</p>';

    $conn->close();
?>
