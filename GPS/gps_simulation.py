import random
import json
import time

# GPS MODULE SIMULATION

def simulate_gps_data():
    """
    Simulates raw GPS data like NEO-6M would output.
    Returns latitude and longitude.
    """
    latitude = round(random.uniform(22.50, 22.60), 6)
    longitude = round(random.uniform(88.30, 88.40), 6)
    return latitude, longitude

# WASTE LEVEL SIMULATION

def simulate_waste_level():
    """
    Simulates ultrasonic sensor reading.
    Returns waste fill percentage.
    """
    return random.randint(0, 100)

# GSM MODULE SIMULATION

def send_sms(message):
    """
    Simulates sending SMS using GSM module.
    """
    print("\n📩 GSM ALERT SENT")
    print("------------------------")
    print(message)
    print("------------------------\n")

# JSON DATA CREATION

def create_json_packet(bin_id, level, latitude, longitude):
    """
    Combines all data into JSON format.
    """
    data = {
        "bin_id": bin_id,
        "fill_percentage": level,
        "latitude": latitude,
        "longitude": longitude,
        "status": "FULL" if level >= 80 else "NORMAL"
    }

    return json.dumps(data, indent=4)

# SELF TEST FUNCTION

def self_test():
    """
    Simulates checking GPS and GSM modules.
    """
    print("🔍 Running Self-Test...")
    time.sleep(1)

    gps_status = True
    gsm_status = True

    if gps_status:
        print("✅ GPS Module OK")
    else:
        print("❌ GPS Module NOT RESPONDING")

    if gsm_status:
        print("✅ GSM Module OK")
    else:
        print("❌ GSM Module NOT RESPONDING")

    print("Self-Test Complete.\n")

# MAIN SYSTEM LOGIC

def main():
    bin_id = 101

    self_test()

    while True:
        print("📡 Reading Sensor Data...\n")

        level = simulate_waste_level()
        latitude, longitude = simulate_gps_data()

        print(f"Fill Level: {level}%")
        print(f"Location: {latitude}, {longitude}")

        json_packet = create_json_packet(bin_id, level, latitude, longitude)

        print("\n📦 JSON Packet:")
        print(json_packet)

        if level >= 80:
            alert_message = f"""
            🚨 ALERT: Bin {bin_id} is FULL!
            Fill Level: {level}%
            Location: {latitude}, {longitude}
            """
            send_sms(alert_message)

        print("\n----------------------------------\n")
        time.sleep(5)


if __name__ == "__main__":
    main()