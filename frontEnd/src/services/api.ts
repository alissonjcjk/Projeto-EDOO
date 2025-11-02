const BASE = import.meta.env.VITE_API_BASE || ''
const USE_MOCK = (import.meta.env.VITE_USE_MOCK || 'true') === 'true'


// dados simulados enquanto a API real não está disponível
const mockClients = [
  { id: 1, name: 'João Silva' },
  { id: 2, name: 'Maria Souza' },
  { id: 3, name: 'Carlos Pereira' },
]

const mockBarbers = [
  { id: 1, name: 'Carlos' },
  { id: 2, name: 'Pedro' },
  { id: 3, name: 'André' },
]

const mockServices = [
  { id: 1, name: 'Corte simples', duration: 30, price: 40 },
  { id: 2, name: 'Corte + barba', duration: 60, price: 80 },
  { id: 3, name: 'Aparar barba', duration: 20, price: 25 },
]

const mockAppointments: Array<any> = []
async function request<T>(path: string) {
  if (USE_MOCK) {
    // no mock mode, retorna dados simulados
    if (path.includes('/clients')) return (mockClients as unknown) as T
    if (path.includes('/barbers')) return (mockBarbers as unknown) as T
    if (path.includes('/services')) return (mockServices as unknown) as T
  }

  //faz requisição real à API
  try {
    const res = await fetch(`${BASE}${path}`, {
      headers: { 'Content-Type': 'application/json' },
    })
    if (!res.ok) {
      const txt = await res.text()
      throw new Error(`API ${res.status}: ${txt}`)
    }
    return (await res.json()) as T
  } catch (err) {

    // fallback para dados simulados em caso de erro
    console.warn('API request failed, falling back to mock data for', path, err)
    if (path.includes('/clients')) return (mockClients as unknown) as T
    if (path.includes('/barbers')) return (mockBarbers as unknown) as T
    if (path.includes('/services')) return (mockServices as unknown) as T
    throw err
  }
}

export const api = {
  getClients: () => request<Array<{ id: number; name: string }>>('/api/clients'),
  getBarbers: () => request<Array<{ id: number; name: string }>>('/api/barbers'),
  getServices: () => request<Array<{ id: number; name: string; duration?: number; price?: number }>>('/api/services'),


  // cria endpoints 
  createClient: (payload: any) => {
    if (USE_MOCK) {
      const id = mockClients.length + 1
      const item = { id, ...payload }
      mockClients.push(item)
      return Promise.resolve(item)
    }
    return fetch(`${BASE}/api/clients`, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(payload) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },
  createBarber: (payload: any) => {
    if (USE_MOCK) {
      const id = mockBarbers.length + 1
      const item = { id, ...payload }
      mockBarbers.push(item)
      return Promise.resolve(item)
    }
    return fetch(`${BASE}/api/barbers`, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(payload) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },
  createAppointment: (payload: any) => {
    if (USE_MOCK) {
      const id = mockAppointments.length + 1
      const item = { id, ...payload }
      mockAppointments.push(item)
      return Promise.resolve(item)
    }
    return fetch(`${BASE}/api/appointments`, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(payload) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  }
}
