import time
import serial
import matplotlib

#matplotlib.use('TkAgg')  # Use TkAgg backend to avoid PyCharm compatibility issues
import matplotlib.pyplot as plt
import matplotlib.animation as animation


def animate(i, dataList, ser, ax):
    """Animation function that updates the plot with new data from Arduino"""
    try:
        ser.write(b'g')  # Transmit the char 'g' to receive the Arduino data point
        arduinoData_string = ser.readline().decode('ascii').strip()  # Decode and strip whitespace

        # Convert to float
        arduinoData_float = float(arduinoData_string)
        dataList.append(arduinoData_float)  # Add to the list

    except ValueError:
        # Log the error but continue
        print(f"Could not convert '{arduinoData_string}' to float")
    except serial.SerialException as e:
        print(f"Serial communication error: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

    # Keep only the last 50 points
    dataList = dataList[-50:]

    # Update plot
    ax.clear()
    ax.plot(dataList)
    ax.set_ylim([0, 6])
    ax.set_title("Arduino Data")
    ax.set_ylabel("Value")
    ax.set_xlabel(f"Sample (Latest: {len(dataList)})")
    ax.grid(True, alpha=0.3)  # Add grid for better readability


def main():
    # Initialize data list
    dataList = []

    # Create figure and axis
    fig, ax = plt.subplots(figsize=(10, 6))

    # Serial port configuration
    commPort = '/dev/cu.usbmodem1101'
    baudRate = 9600

    try:
        # Open serial connection with timeout
        ser = serial.Serial(commPort, baudrate=baudRate, timeout=1)
        print(f"Connected to {commPort} at {baudRate} baud")

        # Wait for Arduino to initialize and send READY signal
        print("Waiting for Arduino to initialize...")
        start_time = time.time()
        ready = False

        while not ready and (time.time() - start_time) < 5:  # 5 second timeout
            if ser.in_waiting:
                line = ser.readline().decode('ascii').strip()
                if line == "READY":
                    ready = True
                    print("Arduino is ready!")
                elif line.startswith("ERROR"):
                    print(f"Arduino error: {line}")
                    return

        if not ready:
            print("Arduino did not initialize properly")
            return

        # Clear any old data in serial buffer
        ser.reset_input_buffer()

        # Create animation
        ani = animation.FuncAnimation(
            fig,
            animate,
            frames=None,  # Run indefinitely
            fargs=(dataList, ser, ax),
            interval=100,  # Update every 100ms
            cache_frame_data=False  # Required for matplotlib 3.10
        )

        # Display the plot
        plt.show()

    except serial.SerialException as e:
        print(f"Error opening serial port: {e}")
        print("Please check:")
        print("- Arduino is connected")
        print("- Correct port is specified")
        print("- No other program is using the port")

    finally:
        # Clean up
        try:
            if 'ser' in locals() and ser.is_open:
                ser.close()
                print("Serial connection closed")
        except:
            pass


if __name__ == "__main__":
    main()

