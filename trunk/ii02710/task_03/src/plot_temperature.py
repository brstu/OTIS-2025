"""
@file plot_temperature.py
@brief Script for visualizing PID controller simulation data
@details Reads data from CSV file and plots temperature and control signal graphs
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Constants
CSV_FILENAME = 'temperature_data.csv'

def plot_temperature_data(csv_file=CSV_FILENAME):
    """
    @brief Plots graphs from CSV data
    @param csv_file Name of CSV file with data
    """
    
    # Check if file exists
    if not os.path.exists(csv_file):
        print(f"Error: File '{csv_file}' not found!")
        print("First run the C++ simulation")
        return
    
    try:
        # Read data from CSV
        data = pd.read_csv(csv_file)
        print(f"Loaded {len(data)} data rows")
        print(f"Columns: {list(data.columns)}")
        
        # Create figure with multiple plots, discard unused figure variable
        _, axes = plt.subplots(3, 1, figsize=(12, 10), sharex=True)
        
        # 1. Temperature plot
        axes[0].plot(data['Time'], data['Temperature'], 'b-', linewidth=2, label='Temperature')
        axes[0].plot(data['Time'], data['Setpoint'], 'r--', linewidth=2, label='Setpoint')
        axes[0].set_ylabel('Temperature (°C)')
        axes[0].set_title('Temperature Control System with PID Controller')
        axes[0].grid(True, alpha=0.3)
        axes[0].legend()
        
        # Calculate and display error statistics
        error = data['Setpoint'] - data['Temperature']
        rmse = np.sqrt(np.mean(error**2))
        max_error = np.max(np.abs(error))
        
        # Add text with statistics
        stats_text = f'RMSE: {rmse:.2f} °C\nMax Error: {max_error:.2f} °C'
        
        # Use dictionary literal instead of dict() constructor
        bbox_props = {
            'boxstyle': 'round',
            'facecolor': 'wheat',
            'alpha': 0.5
        }
        
        axes[0].text(
            0.02, 0.98, stats_text, 
            transform=axes[0].transAxes,
            verticalalignment='top',
            bbox=bbox_props
        )
        
        # 2. Control signal plot
        axes[1].plot(data['Time'], data['Control_Signal'], 'g-', linewidth=2)
        axes[1].fill_between(data['Time'], 0, data['Control_Signal'], alpha=0.3, color='green')
        axes[1].set_ylabel('Control Signal (%)')
        axes[1].set_ylim([0, 105])
        axes[1].grid(True, alpha=0.3)
        axes[1].set_title('Heater Control Signal')
        
        # 3. Control error plot
        axes[2].plot(data['Time'], error, 'r-', linewidth=1.5)
        axes[2].axhline(y=0, color='k', linestyle='-', linewidth=0.5)
        axes[2].fill_between(
            data['Time'], 0, error, 
            where=(error >= 0), 
            alpha=0.3, color='red', interpolate=True
        )
        axes[2].fill_between(
            data['Time'], 0, error, 
            where=(error < 0), 
            alpha=0.3, color='blue', interpolate=True
        )
        axes[2].set_xlabel('Time (seconds)')
        axes[2].set_ylabel('Error (°C)')
        axes[2].grid(True, alpha=0.3)
        axes[2].set_title('Control Error')
        
        # Adjust layout
        plt.suptitle('PID Controller Performance Analysis', fontsize=14, fontweight='bold')
        plt.tight_layout()
        
        # Save plots
        plt.savefig('temperature_plot.png', dpi=300, bbox_inches='tight')
        plt.savefig('temperature_plot.pdf', bbox_inches='tight')
        
        # Show plot
        plt.show()
        
        # Print statistics to console
        print_statistics(data, rmse, max_error)
        
    except Exception as e:
        print(f"Error processing file: {e}")


def print_statistics(data, rmse, max_error):
    """Print simulation statistics to console"""
    print("\n=== Statistics ===")
    print(f"Time range: {data['Time'].min():.1f} - {data['Time'].max():.1f} s")
    print(f"Average temperature: {data['Temperature'].mean():.2f} °C")
    print(f"Average control signal: {data['Control_Signal'].mean():.2f} %")
    print(f"Root Mean Square Error (RMSE): {rmse:.2f} °C")
    print(f"Maximum error: {max_error:.2f} °C")


def plot_phase_plane(csv_file=CSV_FILENAME):
    """
    @brief Plots phase plane of the system
    @param csv_file Name of CSV file with data
    """
    
    try:
        data = pd.read_csv(csv_file)
        
        # Calculate temperature derivative (rate of change)
        temp_diff = np.diff(data['Temperature']) / np.diff(data['Time'])
        temp_diff = np.insert(temp_diff, 0, np.nan)
        
        # Create phase plane plot
        plt.figure(figsize=(10, 6))
        
        # Use color to indicate time
        scatter = plt.scatter(
            data['Temperature'][1:], 
            temp_diff[1:], 
            c=data['Time'][1:], 
            cmap='viridis', 
            s=20, 
            alpha=0.7
        )
        
        plt.xlabel('Temperature (°C)')
        plt.ylabel('dT/dt (°C/s)')
        plt.title('System Phase Plane')
        plt.grid(True, alpha=0.3)
        
        # Add color bar for time
        cbar = plt.colorbar(scatter)
        cbar.set_label('Time (s)')
        
        # Save plot
        plt.savefig('phase_plane.png', dpi=300, bbox_inches='tight')
        plt.show()
        
    except Exception as e:
        print(f"Error creating phase plane: {e}")


def analyze_setpoint_changes(data, change_indices):
    """Analyze system response to setpoint changes"""
    print("\n=== Transient Process Analysis ===")
    
    for i, change_idx in enumerate(change_indices):
        if change_idx < len(data) - 10:
            self._analyze_single_change(data, i, change_idx)


def _analyze_single_change(self, data, change_number, change_index):
    """Analyze a single setpoint change"""
    start_time = data['Time'][change_index]
    new_setpoint = data['Setpoint'][change_index + 1]
    old_setpoint = data['Setpoint'][change_index]
    
    print(f"\nChange {change_number + 1}: {old_setpoint:.1f} → {new_setpoint:.1f} °C at {start_time:.1f} s")
    
    window = data.iloc[change_index:change_index + 100]
    
    if len(window) > 1:
        self._calculate_settling_time(window, new_setpoint, old_setpoint, start_time)
        self._calculate_overshoot(window, new_setpoint, old_setpoint)


def _calculate_settling_time(self, window, new_setpoint, old_setpoint, start_time):
    """Calculate settling time for a setpoint change"""
    tolerance = 0.05 * abs(new_setpoint - old_setpoint)
    condition = np.abs(window['Temperature'] - new_setpoint) < tolerance
    settled_indices = np.nonzero(condition)[0]
    
    if len(settled_indices) > 0:
        settle_time = window.iloc[settled_indices[0]]['Time'] - start_time
        print(f"  Settling time: {settle_time:.2f} s")

def _calculate_overshoot(self, window, new_setpoint, old_setpoint):
    """Calculate overshoot for a setpoint change"""
    if new_setpoint > old_setpoint:
        max_temp = window['Temperature'].max()
        overshoot = ((max_temp - new_setpoint) / (new_setpoint - old_setpoint)) * 100
        print(f"  Overshoot: {overshoot:.1f} %")


def analyze_steady_state(data):
    """Analyze system performance in steady state"""
    print("\n=== Steady State Analysis ===")
    
    # Use last 20 seconds as steady state
    steady_state_mask = data['Time'] > 80
    steady_state_data = data[steady_state_mask]
    
    if len(steady_state_data) > 0:
        temp_std = steady_state_data['Temperature'].std()
        control_std = steady_state_data['Control_Signal'].std()
        
        print(f"Temperature standard deviation: {temp_std:.3f} °C")
        print(f"Control signal standard deviation: {control_std:.2f} %")
        
        # Energy usage coefficient
        avg_control = steady_state_data['Control_Signal'].mean()
        print(f"Average heating power: {avg_control:.1f} %")


def analyze_performance(csv_file=CSV_FILENAME):
    """
    @brief Analyze system performance
    @param csv_file Name of CSV file with data
    """
    
    try:
        data = pd.read_csv(csv_file)
        
        # Find setpoint change moments using np.nonzero
        setpoint_differences = np.diff(data['Setpoint']) != 0
        setpoint_changes = np.nonzero(setpoint_differences)[0]
        
        if len(setpoint_changes) > 0:
            self.analyze_setpoint_changes(data, setpoint_changes)
        
        self.analyze_steady_state(data)
        
    except Exception as e:
        print(f"Error in performance analysis: {e}")


if __name__ == "__main__":
    print("Starting PID controller data analysis...")
    print("=" * 50)
    
    # Main plot
    plot_temperature_data()
    
    # Phase plane (with exception handling)
    try:
        plot_phase_plane()
    except Exception as e:
        print(f"\nFailed to create phase plane: {e}")
    
    # Performance analysis
    try:
        analyze_performance()
    except Exception as e:
        print(f"Failed to analyze performance: {e}")
    
    print("\n" + "=" * 50)
    print("Analysis complete. Saved plots:")
    print("  - temperature_plot.png")
    print("  - temperature_plot.pdf")
    print("  - phase_plane.png (if available)")