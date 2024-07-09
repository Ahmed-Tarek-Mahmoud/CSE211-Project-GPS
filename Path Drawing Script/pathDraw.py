import gmplot   

with open(r'D:\Junior CSE\putty logs\putty.txt') as file:

    save_lines = False
    tuples_array=[]
    for line in file:
        if 'Lats   Longs' in line:
            save_lines= True
            continue
        if save_lines:
            numbers = line.split()
            if len(numbers) == 2:
                num1 = float(numbers[0])
                num2 = float(numbers[1])
                tuples_array.append((num1,num2))
# Initialize the map
gmap = gmplot.GoogleMapPlotter(0, 0, 2)

gps_data = tuples_array
#[(40.7128, -74.0060), (34.0522, -118.2437), (37.7749, -122.4194)]  # Example coordinates

# Extract latitude and longitude
lats = [lat for lat, lon in gps_data]
lons = [lon for lat, lon in gps_data]

# Plot path
gmap.plot(lats, lons, 'cornflowerblue', edge_width=5)

# Save the map
gmap.draw("path.html")