namespace WindowsFormsApp1
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBoxConnection = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.comboBoxHandShake = new System.Windows.Forms.ComboBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.comboPorts = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.comboParity = new System.Windows.Forms.ComboBox();
            this.comboStopBit = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBits = new System.Windows.Forms.ComboBox();
            this.comboBaud = new System.Windows.Forms.ComboBox();
            this.MySerial = new System.IO.Ports.SerialPort(this.components);
            this.buttonExit = new System.Windows.Forms.Button();
            this.groupBoxIO = new System.Windows.Forms.GroupBox();
            this.buttonL4Off = new System.Windows.Forms.Button();
            this.buttonL4On = new System.Windows.Forms.Button();
            this.buttonL3Off = new System.Windows.Forms.Button();
            this.buttonL3On = new System.Windows.Forms.Button();
            this.buttonL2Off = new System.Windows.Forms.Button();
            this.buttonL2On = new System.Windows.Forms.Button();
            this.buttonL1Off = new System.Windows.Forms.Button();
            this.buttonL1On = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.buttonClear = new System.Windows.Forms.Button();
            this.groupBoxConnection.SuspendLayout();
            this.groupBoxIO.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxConnection
            // 
            this.groupBoxConnection.Controls.Add(this.label6);
            this.groupBoxConnection.Controls.Add(this.comboBoxHandShake);
            this.groupBoxConnection.Controls.Add(this.buttonConnect);
            this.groupBoxConnection.Controls.Add(this.comboPorts);
            this.groupBoxConnection.Controls.Add(this.label5);
            this.groupBoxConnection.Controls.Add(this.label1);
            this.groupBoxConnection.Controls.Add(this.label2);
            this.groupBoxConnection.Controls.Add(this.comboParity);
            this.groupBoxConnection.Controls.Add(this.comboStopBit);
            this.groupBoxConnection.Controls.Add(this.label4);
            this.groupBoxConnection.Controls.Add(this.label3);
            this.groupBoxConnection.Controls.Add(this.comboBits);
            this.groupBoxConnection.Controls.Add(this.comboBaud);
            this.groupBoxConnection.Location = new System.Drawing.Point(12, 12);
            this.groupBoxConnection.Name = "groupBoxConnection";
            this.groupBoxConnection.Size = new System.Drawing.Size(164, 216);
            this.groupBoxConnection.TabIndex = 0;
            this.groupBoxConnection.TabStop = false;
            this.groupBoxConnection.Text = "Connection";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(-3, 162);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(73, 13);
            this.label6.TabIndex = 30;
            this.label6.Text = "Hand Shake :";
            // 
            // comboBoxHandShake
            // 
            this.comboBoxHandShake.FormattingEnabled = true;
            this.comboBoxHandShake.Location = new System.Drawing.Point(76, 159);
            this.comboBoxHandShake.Name = "comboBoxHandShake";
            this.comboBoxHandShake.Size = new System.Drawing.Size(75, 21);
            this.comboBoxHandShake.TabIndex = 29;
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(76, 189);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 28;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // comboPorts
            // 
            this.comboPorts.FormattingEnabled = true;
            this.comboPorts.Location = new System.Drawing.Point(76, 24);
            this.comboPorts.Name = "comboPorts";
            this.comboPorts.Size = new System.Drawing.Size(75, 21);
            this.comboPorts.TabIndex = 19;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(20, 135);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(50, 13);
            this.label5.TabIndex = 27;
            this.label5.Text = "Stop Bit :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 13);
            this.label1.TabIndex = 23;
            this.label1.Text = "COM Port :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 54);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 13);
            this.label2.TabIndex = 24;
            this.label2.Text = "Baud Rate :";
            // 
            // comboParity
            // 
            this.comboParity.FormattingEnabled = true;
            this.comboParity.Location = new System.Drawing.Point(76, 105);
            this.comboParity.Name = "comboParity";
            this.comboParity.Size = new System.Drawing.Size(75, 21);
            this.comboParity.TabIndex = 21;
            // 
            // comboStopBit
            // 
            this.comboStopBit.FormattingEnabled = true;
            this.comboStopBit.Location = new System.Drawing.Point(76, 132);
            this.comboStopBit.Name = "comboStopBit";
            this.comboStopBit.Size = new System.Drawing.Size(75, 21);
            this.comboStopBit.TabIndex = 22;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(16, 108);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(54, 13);
            this.label4.TabIndex = 26;
            this.label4.Text = "Parity Bit :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 81);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(51, 13);
            this.label3.TabIndex = 25;
            this.label3.Text = "Data Bit :";
            // 
            // comboBits
            // 
            this.comboBits.FormattingEnabled = true;
            this.comboBits.Location = new System.Drawing.Point(76, 78);
            this.comboBits.Name = "comboBits";
            this.comboBits.Size = new System.Drawing.Size(75, 21);
            this.comboBits.TabIndex = 20;
            // 
            // comboBaud
            // 
            this.comboBaud.FormattingEnabled = true;
            this.comboBaud.Location = new System.Drawing.Point(76, 51);
            this.comboBaud.Name = "comboBaud";
            this.comboBaud.Size = new System.Drawing.Size(75, 21);
            this.comboBaud.TabIndex = 18;
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(282, 400);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(75, 23);
            this.buttonExit.TabIndex = 1;
            this.buttonExit.Text = "Exit";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // groupBoxIO
            // 
            this.groupBoxIO.Controls.Add(this.buttonL4Off);
            this.groupBoxIO.Controls.Add(this.buttonL4On);
            this.groupBoxIO.Controls.Add(this.buttonL3Off);
            this.groupBoxIO.Controls.Add(this.buttonL3On);
            this.groupBoxIO.Controls.Add(this.buttonL2Off);
            this.groupBoxIO.Controls.Add(this.buttonL2On);
            this.groupBoxIO.Controls.Add(this.buttonL1Off);
            this.groupBoxIO.Controls.Add(this.buttonL1On);
            this.groupBoxIO.Enabled = false;
            this.groupBoxIO.Location = new System.Drawing.Point(182, 12);
            this.groupBoxIO.Name = "groupBoxIO";
            this.groupBoxIO.Size = new System.Drawing.Size(175, 216);
            this.groupBoxIO.TabIndex = 12;
            this.groupBoxIO.TabStop = false;
            this.groupBoxIO.Text = "Output";
            // 
            // buttonL4Off
            // 
            this.buttonL4Off.Location = new System.Drawing.Point(88, 108);
            this.buttonL4Off.Name = "buttonL4Off";
            this.buttonL4Off.Size = new System.Drawing.Size(75, 23);
            this.buttonL4Off.TabIndex = 7;
            this.buttonL4Off.Text = "LED 4 OFF";
            this.buttonL4Off.UseVisualStyleBackColor = true;
            this.buttonL4Off.Click += new System.EventHandler(this.buttonL4Off_Click);
            // 
            // buttonL4On
            // 
            this.buttonL4On.Location = new System.Drawing.Point(7, 108);
            this.buttonL4On.Name = "buttonL4On";
            this.buttonL4On.Size = new System.Drawing.Size(75, 23);
            this.buttonL4On.TabIndex = 6;
            this.buttonL4On.Text = "LED 4 ON";
            this.buttonL4On.UseVisualStyleBackColor = true;
            this.buttonL4On.Click += new System.EventHandler(this.buttonL4On_Click);
            // 
            // buttonL3Off
            // 
            this.buttonL3Off.Location = new System.Drawing.Point(88, 79);
            this.buttonL3Off.Name = "buttonL3Off";
            this.buttonL3Off.Size = new System.Drawing.Size(75, 23);
            this.buttonL3Off.TabIndex = 5;
            this.buttonL3Off.Text = "LED 3 OFF";
            this.buttonL3Off.UseVisualStyleBackColor = true;
            this.buttonL3Off.Click += new System.EventHandler(this.buttonL3Off_Click);
            // 
            // buttonL3On
            // 
            this.buttonL3On.Location = new System.Drawing.Point(7, 79);
            this.buttonL3On.Name = "buttonL3On";
            this.buttonL3On.Size = new System.Drawing.Size(75, 23);
            this.buttonL3On.TabIndex = 4;
            this.buttonL3On.Text = "LED 3 ON";
            this.buttonL3On.UseVisualStyleBackColor = true;
            this.buttonL3On.Click += new System.EventHandler(this.buttonL3On_Click);
            // 
            // buttonL2Off
            // 
            this.buttonL2Off.Location = new System.Drawing.Point(88, 50);
            this.buttonL2Off.Name = "buttonL2Off";
            this.buttonL2Off.Size = new System.Drawing.Size(75, 23);
            this.buttonL2Off.TabIndex = 3;
            this.buttonL2Off.Text = "LED 2 OFF";
            this.buttonL2Off.UseVisualStyleBackColor = true;
            this.buttonL2Off.Click += new System.EventHandler(this.buttonL2Off_Click);
            // 
            // buttonL2On
            // 
            this.buttonL2On.Location = new System.Drawing.Point(7, 50);
            this.buttonL2On.Name = "buttonL2On";
            this.buttonL2On.Size = new System.Drawing.Size(75, 23);
            this.buttonL2On.TabIndex = 2;
            this.buttonL2On.Text = "LED 2 ON";
            this.buttonL2On.UseVisualStyleBackColor = true;
            this.buttonL2On.Click += new System.EventHandler(this.buttonL2On_Click);
            // 
            // buttonL1Off
            // 
            this.buttonL1Off.Location = new System.Drawing.Point(88, 21);
            this.buttonL1Off.Name = "buttonL1Off";
            this.buttonL1Off.Size = new System.Drawing.Size(75, 23);
            this.buttonL1Off.TabIndex = 1;
            this.buttonL1Off.Text = "LED 1 OFF";
            this.buttonL1Off.UseVisualStyleBackColor = true;
            this.buttonL1Off.Click += new System.EventHandler(this.buttonL1Off_Click);
            // 
            // buttonL1On
            // 
            this.buttonL1On.Location = new System.Drawing.Point(7, 21);
            this.buttonL1On.Name = "buttonL1On";
            this.buttonL1On.Size = new System.Drawing.Size(75, 23);
            this.buttonL1On.TabIndex = 0;
            this.buttonL1On.Text = "LED 1 ON";
            this.buttonL1On.UseVisualStyleBackColor = true;
            this.buttonL1On.Click += new System.EventHandler(this.buttonL1On_Click);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(12, 234);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(345, 160);
            this.listBox1.TabIndex = 13;
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(12, 400);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(75, 23);
            this.buttonClear.TabIndex = 14;
            this.buttonClear.Text = "Clear";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(367, 433);
            this.Controls.Add(this.buttonClear);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.groupBoxIO);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.groupBoxConnection);
            this.Name = "mainForm";
            this.Text = "Serial Control";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.mainForm_FormClosing);
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.groupBoxConnection.ResumeLayout(false);
            this.groupBoxConnection.PerformLayout();
            this.groupBoxIO.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxConnection;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.ComboBox comboPorts;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboParity;
        private System.Windows.Forms.ComboBox comboStopBit;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBits;
        private System.Windows.Forms.ComboBox comboBaud;
        private System.IO.Ports.SerialPort MySerial;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comboBoxHandShake;
        private System.Windows.Forms.GroupBox groupBoxIO;
        private System.Windows.Forms.Button buttonL4Off;
        private System.Windows.Forms.Button buttonL4On;
        private System.Windows.Forms.Button buttonL3Off;
        private System.Windows.Forms.Button buttonL3On;
        private System.Windows.Forms.Button buttonL2Off;
        private System.Windows.Forms.Button buttonL2On;
        private System.Windows.Forms.Button buttonL1Off;
        private System.Windows.Forms.Button buttonL1On;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button buttonClear;
    }
}

