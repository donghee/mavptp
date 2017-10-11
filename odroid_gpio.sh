echo 173 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio173/direction

echo 1 > /sys/class/gpio/gpio173/value
sleep 1
echo 0 > /sys/class/gpio/gpio173/value
sleep 1

echo 1 > /sys/class/gpio/gpio173/value
sleep 1
echo 0 > /sys/class/gpio/gpio173/value
sleep 1

echo 1 > /sys/class/gpio/gpio173/value
sleep 1
echo 0 > /sys/class/gpio/gpio173/value
sleep 1

echo 1 > /sys/class/gpio/gpio173/value
sleep 1
echo 0 > /sys/class/gpio/gpio173/value
sleep 1

echo 1 > /sys/class/gpio/gpio173/value
sleep 1
echo 0 > /sys/class/gpio/gpio173/value
sleep 1

