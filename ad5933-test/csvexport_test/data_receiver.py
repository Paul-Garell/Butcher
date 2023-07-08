import serial
import csv

# Specify the Bluetooth serial port name
bluetooth_port = '/dev/tty.YourBluetoothSerialPort'  # Replace with your Bluetooth serial port

# Specify the baud rate (must match the baud rate used in Arduino code)
baud_rate = 9600

# Specify the file name for saving the CSV data
csv_file = 'data.csv'

# Open the Bluetooth serial connection
ser = serial.Serial(bluetooth_port, baud_rate)

# Create a CSV file and a CSV writer
with open(csv_file, 'w') as file:
    writer = csv.writer(file)

    # Read data from the Bluetooth serial connection and save it as CSV
    while True:
        # Read a line of data from the serial connection
        line = ser.readline().decode().strip()
        
        # Split the line by comma to separate values
        data = line.split(',')

        # Write the data to the CSV file
        writer.writerow(data)

        # Print the received data (optional)
        print(data)

# Close the Bluetooth serial connection
ser.close()
