// services/api.ts
const API_BASE_URL = 'http://localhost:8080/api';

export const api = {
  // Clientes
  async getClients() {
    const response = await fetch(`${API_BASE_URL}/clients`);
    return await response.json();
  },

  async createClient(clientData: { name: string; email: string; phone: string ; servicoPreferido: string}) {
    const response = await fetch(`${API_BASE_URL}/clients`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(clientData),
    });
    return await response.json();
  },

  // Barbeiros
  async getBarbers() {
    const response = await fetch(`${API_BASE_URL}/barbers`);
    return await response.json();
  },

  async createBarber(barberData: { 
    name: string; 
    role: string; 
    startTime: string; 
    endTime: string; 
    salary: number 
  }) {
    const response = await fetch(`${API_BASE_URL}/barbers`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        name: barberData.name,
        email: "", // Adaptar conforme necessário
        phone: "", // Adaptar conforme necessário
        specialty: barberData.role
      }),
    });
    return await response.json();
  },

  // Serviços
  async getServices() {
    const response = await fetch(`${API_BASE_URL}/services`);
    return await response.json();
  },

  // Agendamentos
  async createAppointment(appointmentData: {
    clientId: number;
    barberId: number;
    serviceId: number;
    date: string;
    time: string;
    status: string;
  }) {
    const response = await fetch(`${API_BASE_URL}/appointments`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(appointmentData),
    });
    return await response.json();
  },

  async getAppointments() {
    const response = await fetch(`${API_BASE_URL}/appointments`);
    return await response.json();
  }
};