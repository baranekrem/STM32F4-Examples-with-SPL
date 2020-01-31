using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class mainForm : Form
    {
        byte[] dataPacket = new byte[5];

        public mainForm()
        {
            InitializeComponent();
        }

        private void mainForm_Load(object sender, EventArgs e)
        {
            string[] portNames = SerialPort.GetPortNames();
            int[] baudRates = { 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 };
            int[] dataBits = { 5, 6, 7, 8 };

            comboPorts.DataSource = portNames;
            comboBaud.DataSource = baudRates;
            comboBits.DataSource = dataBits;
            comboParity.DataSource = Enum.GetValues(typeof(Parity));
            comboStopBit.DataSource = Enum.GetValues(typeof(StopBits));
            comboBoxHandShake.DataSource = Enum.GetValues(typeof(Handshake));

            comboPorts.Text = portNames[0].ToString();
            comboBaud.Text = baudRates[5].ToString();
            comboBits.Text = dataBits[3].ToString();
            comboParity.Text = Parity.None.ToString();
            comboStopBit.Text = StopBits.One.ToString();
            comboBoxHandShake.Text = Handshake.None.ToString();

            CheckForIllegalCrossThreadCalls = false;

            dataPacket[0] = (byte)'X';
            dataPacket[1] = (byte)'Y';
            dataPacket[2] = (byte)0;
            dataPacket[3] = (byte)0;
            dataPacket[4] = (byte)'Z';
        }

        internal delegate void SerialDataReceivedEventHandlerDelegate(object sender, SerialDataReceivedEventArgs e);

        private void SerialPort_ReceivedEvent(object sender, SerialDataReceivedEventArgs e)
        {
            string data = MySerial.ReadLine();

            listBox1.Items.Add(data);
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            if (!MySerial.IsOpen)
            {
                try
                {
                    MySerial.PortName = Convert.ToString(comboPorts.Text);
                    MySerial.BaudRate = Convert.ToInt32(comboBaud.Text);
                    MySerial.DataBits = Convert.ToInt16(comboBits.Text);
                    MySerial.Parity = (Parity)Enum.Parse(typeof(Parity), comboParity.Text);
                    MySerial.StopBits = (StopBits)Enum.Parse(typeof(StopBits), comboStopBit.Text);
                    MySerial.DataReceived += new SerialDataReceivedEventHandler(SerialPort_ReceivedEvent);
                    MySerial.Handshake = (Handshake)Enum.Parse(typeof(Handshake), comboBoxHandShake.Text);
                    MySerial.Open();

                    buttonConnect.Text = "Disconnect";
                    comboPorts.Enabled = false;
                    comboBaud.Enabled = false;
                    comboBits.Enabled = false;
                    comboParity.Enabled = false;
                    comboStopBit.Enabled = false;
                    comboBoxHandShake.Enabled = false;

                    groupBoxIO.Enabled = true;
                }
                catch (Exception)
                {
                    MessageBox.Show("Connection Error", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    MySerial.Close();
                    buttonConnect.Text = "Connect";
                    comboPorts.Enabled = true;
                    comboBaud.Enabled = true;
                    comboBits.Enabled = true;
                    comboParity.Enabled = true;
                    comboStopBit.Enabled = true;
                    comboBoxHandShake.Enabled = true;

                    groupBoxIO.Enabled = false;
                }
            }
            else
            {
                MySerial.Close();
                buttonConnect.Text = "Connect";
                comboPorts.Enabled = true;
                comboBaud.Enabled = true;
                comboBits.Enabled = true;
                comboParity.Enabled = true;
                comboStopBit.Enabled = true;
                comboBoxHandShake.Enabled = true;

                groupBoxIO.Enabled = false;
            }
        }

        private void buttonL1On_Click(object sender, EventArgs e)
        {
            dataPacket[2] = (byte)1;
            dataPacket[3] = (byte)1;

            MySerial.Write(dataPacket, 0, dataPacket.Length);
        }

        private void buttonL1Off_Click(object sender, EventArgs e)
        {
            dataPacket[2] = (byte)1;
            dataPacket[3] = (byte)0;

            MySerial.Write(dataPacket, 0, dataPacket.Length);
        }

        private void buttonL2On_Click(object sender, EventArgs e)
        {
            dataPacket[2] = (byte)2;
            dataPacket[3] = (byte)1;

            MySerial.Write(dataPacket, 0, dataPacket.Length);
        }

        private void buttonL2Off_Click(object sender, EventArgs e)
        {
            dataPacket[2] = (byte)2;
            dataPacket[3] = (byte)0;

            MySerial.Write(dataPacket, 0, dataPacket.Length);
        }

        private void buttonL3On_Click(object sender, EventArgs e)
        {
            dataPacket[2] = (byte)3;
            dataPacket[3] = (byte)1;

            MySerial.Write(dataPacket, 0, dataPacket.Length);
        }

        private void buttonL3Off_Click(object sender, EventArgs e)
        {
            dataPacket[2] = (byte)3;
            dataPacket[3] = (byte)0;

            MySerial.Write(dataPacket, 0, dataPacket.Length);
        }

        private void buttonL4On_Click(object sender, EventArgs e)
        {
            dataPacket[2] = (byte)4;
            dataPacket[3] = (byte)1;

            MySerial.Write(dataPacket, 0, dataPacket.Length);
        }

        private void buttonL4Off_Click(object sender, EventArgs e)
        {
            dataPacket[2] = (byte)4;
            dataPacket[3] = (byte)0;

            MySerial.Write(dataPacket, 0, dataPacket.Length);
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            DialogResult result;

            result = MessageBox.Show("Are you sure you want to exit ?", "Warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

            if (result == DialogResult.Yes)
            {
                if (MySerial.IsOpen)
                    MySerial.Close();

                try
                {
                    Environment.Exit(1);
                }
                catch (Exception)
                {
                }
            }
        }

        private void mainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            Application.Exit();
        }
    }
}
