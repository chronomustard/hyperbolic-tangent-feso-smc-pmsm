# Hyperbolic Tangent Function Extended State Observer with Sliding Mode Control for PMSM Control Modelling and Simulation

This repository contains the implementation of a control system for Permanent Magnet Synchronous Motors (PMSMs) using the Hyperbolic Tangent Function Extended State Observer (HTF-ESO) combined with Sliding Mode Control (SMC) techniques. The objective of this project is to achieve precise speed regulation and disturbance rejection in PMSM systems.

## Project Description

The project focuses on developing and simulating a control system for PMSM systems based on the research articles by Y. Wang et al. and X. Zhang et al. The proposed approach combines the HTF-ESO and SMC techniques to enhance the speed control performance and mitigate disturbances in PMSM systems.

The key objectives of this project are as follows:

1. Implementing the HTF-ESO algorithm for state estimation in PMSM systems.
2. Designing a sliding mode controller to regulate the speed of the PMSM accurately.
3. Investigating the effectiveness of the proposed control approach in rejecting disturbances and maintaining stable operation.
4. Conducting comprehensive simulations to evaluate the performance of the control system under various operating conditions and load profiles.

The project includes MATLAB and CMEX simulation models that leverage the mathematical foundations and control algorithms described in the research articles. The HTF-ESO is utilized as an observer to estimate the system states, including the rotor speed and disturbances, while the SMC algorithm ensures robust and precise control of the PMSM.

## ESO-SMSC

### Simulink Block

![image](https://github.com/chronomustard/hyperbolic-tangent-feso-smc-pmsm/assets/70846916/fb4445f2-ed8d-4348-82a2-f8b8126d0dbb)

### HTF ESO

![image](https://github.com/chronomustard/hyperbolic-tangent-feso-smc-pmsm/assets/70846916/a1899e26-fab1-40e5-983e-52892ed3dd81)

### Q-axis Current Reference

![image](https://github.com/chronomustard/hyperbolic-tangent-feso-smc-pmsm/assets/70846916/0a193dff-5d4b-4541-9d1c-f9c46176f8fe)

![image](https://github.com/chronomustard/hyperbolic-tangent-feso-smc-pmsm/assets/70846916/7bc7ed42-02fa-4ca0-b538-740062931feb)

### Simulation Results

#### Changing Reference Signal

Load Torque: 0 Nm
Reference Speed: 0 to 500 rpm on t = 1 second and 500 to 250 rpm on t = 5 second
![image](https://github.com/chronomustard/hyperbolic-tangent-feso-smc-pmsm/assets/70846916/f20b969e-0939-4963-979d-383b12ab1a4e)

#### Changing Load Torque (0 - 5 Nm)

Load Torque: 0 to 5 Nm on t = 2 second
Reference Speed: 0 to 500 rpm on t = 1 second
![image](https://github.com/chronomustard/hyperbolic-tangent-feso-smc-pmsm/assets/70846916/db2689dd-1adc-4e37-abbf-6cb6f0a99e8c)

## How to Use

1. Clone this repository to your local machine using the following command:
   ```
   git clone https://github.com/your-username/hyperbolic-tangent-feso-smc-pmsm.git
   ```

2. Open MATLAB and navigate to the cloned repository directory.

3. Run the simulation script `RUNTHIS.slx` to execute the PMSM control simulation.

4. Customize the simulation parameters, load profiles, and control settings as desired in the script.

5. Analyze the simulation results and evaluate the performance of the HTF-ESO with SMC control system.

## Contributing

Contributions to this project are welcome. If you would like to contribute, please follow these steps:

1. Fork the repository.

2. Create a new branch for your contribution.

3. Make your changes and enhancements.

4. Test your changes to ensure they work as expected.

5. Submit a pull request with a detailed description of your changes.

## References

1. Y. Wang, Y. Feng, X. Zhang, and J. Liang, "A new reaching law for Antidisturbance sliding-mode control of PMSM Speed Regulation System," IEEE Transactions on Power Electronics, vol. 35, no. 4, pp. 4117–4126, 2020. doi:10.1109/tpel.2019.2933613

2. X. Zhang, L. Sun, K. Zhao, and L. Sun, "Nonlinear Speed Control for PMSM system using sliding-mode control and disturbance compensation techniques," IEEE Transactions on Power Electronics, vol. 28, no. 3, pp. 1358–1365, 2013. doi:10.1109/tpel.2012.2206610

## License

This project is licensed under the [MIT License](LICENSE).
