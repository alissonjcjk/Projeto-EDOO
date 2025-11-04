const BASE = import.meta.env.VITE_API_BASE || ''
const USE_MOCK = (import.meta.env.VITE_USE_MOCK || 'true') === 'true'


// dados simulados enquanto a API real não está disponível
const mockClients = [
  { id: 1, name: 'João Silva', email: 'joao@example.com', phone: '(11) 99999-0001' },
  { id: 2, name: 'Maria Souza', email: 'maria@example.com', phone: '(11) 99999-0002' },
  { id: 3, name: 'Carlos Pereira', email: 'carlos@example.com', phone: '(11) 99999-0003' },
]

const mockBarbers = [
  { id: 1, name: 'Carlos' },
  { id: 2, name: 'Pedro' },
  { id: 3, name: 'André' },
]

const mockServices = [
  { id: 1, name: 'Corte simples', duracao: 30, preco: 40 },
  { id: 2, name: 'Corte + barba', duracao: 60, preco: 80 },
  { id: 3, name: 'Aparar barba', duracao: 20, preco: 25 },
]

const mockGestores = [
  { id: 1, nome: 'Gestor 1', email: 'gestor@example.com' }
]

const mockAppointments: Array<any> = []

async function request<T>(path: string) {
  if (USE_MOCK) {
    // suporta rotas em inglês e português para desenvolvimento
    if (path.includes('/clients') || path.includes('/clientes')) return (mockClients as unknown) as T
    if (path.includes('/barbers') || path.includes('/barbeiros')) return (mockBarbers as unknown) as T
    if (path.includes('/services') || path.includes('/servicos')) return (mockServices as unknown) as T
    if (path.includes('/gestores')) return (mockGestores as unknown) as T
  }

  // faz requisição real à API
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
    if (path.includes('/clients') || path.includes('/clientes')) return (mockClients as unknown) as T
    if (path.includes('/barbers') || path.includes('/barbeiros')) return (mockBarbers as unknown) as T
    if (path.includes('/services') || path.includes('/servicos')) return (mockServices as unknown) as T
    if (path.includes('/gestores')) return (mockGestores as unknown) as T
    throw err
  }
}

export const api = {
  // Clientes
  getClients: () => request<Array<{ id: number; name: string }>>('/clientes'),
  getClient: (id: number) => request<any>(`/cliente/${id}`),
  createClient: (payload: any) => {
    
    const body = {
      nome: payload.nome || payload.name,
      email: payload.email,
      telefone: payload.phone || payload.telefone,
      servico_preferido: payload.servico_preferido || payload.preferredServiceId || payload.servico_preferido,
    }
    if (USE_MOCK) {
      const id = mockClients.length + 1
      const item = { id, name: body.nome, email: body.email, phone: body.telefone }
      mockClients.push(item)
      return Promise.resolve(item)
    }
    return fetch(`${BASE}/cliente`, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(body) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },

  // Barbeiros
  getBarbers: () => request<Array<{ id: number; name: string }>>('/barbeiros'),
  getBarber: (id: number) => request<any>(`/barbeiro/${id}`),
  createBarber: (payload: any) => {
    const body = { nome: payload.nome || payload.name, email: payload.email, telefone: payload.telefone || payload.phone, salario: payload.salario || payload.salary }
    if (USE_MOCK) {
      const id = mockBarbers.length + 1
      const item = { id, name: body.nome }
      mockBarbers.push(item)
      return Promise.resolve(item)
    }
    return fetch(`${BASE}/barbeiro`, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(body) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },

  // Serviços
  getServices: () => request<Array<{ id: number; name: string; duracao?: number; preco?: number }>>('/servicos'),
  getService: (id: number) => request<any>(`/servico/${id}`),
  createService: (payload: any) => {

    const body = { nome: payload.name || payload.nome, preco: payload.price || payload.preco, duracao: payload.duration || payload.duracao }
    if (USE_MOCK) {
      const id = mockServices.length + 1
      const item = { id, name: body.nome || `Servico ${id}`, duracao: body.duracao || 0, preco: body.preco || 0 }
      mockServices.push(item)
      return Promise.resolve(item)
    }
    return fetch(`${BASE}/servico`, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(body) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },
  updateService: (id: number, payload: any) => {
    // payload expected as { nome?, preco?, duracao? } or similar
    const body = { nome: payload.name || payload.nome, preco: payload.price ?? payload.preco, duracao: payload.duration ?? payload.duracao }
    if (USE_MOCK) {
      const s = mockServices.find((x) => x.id === id)
      if (s) {
        if (body.nome) s.name = body.nome
        if (body.preco !== undefined) s.preco = body.preco
        if (body.duracao !== undefined) s.duracao = body.duracao
      }
      return Promise.resolve(s)
    }
    return fetch(`${BASE}/servico/${id}`, { method: 'PUT', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(body) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },
  deleteService: (id: number) => {
    if (USE_MOCK) {
      const idx = mockServices.findIndex((x) => x.id === id)
      if (idx >= 0) mockServices.splice(idx, 1)
      return Promise.resolve({ success: true })
    }
    return fetch(`${BASE}/servico/${id}`, { method: 'DELETE' }).then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },
  updateServiceValor: (id: number, novo_valor: number) => {
    if (USE_MOCK) {
      const s = mockServices.find((x) => x.id === id)
      if (s) s.preco = novo_valor
      return Promise.resolve(s)
    }
    return fetch(`${BASE}/servicos/${id}/valor`, { method: 'PUT', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify({ novo_valor }) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },
  updateServiceDuracao: (id: number, nova_duracao: number) => {
    if (USE_MOCK) {
      const s = mockServices.find((x) => x.id === id)
      if (s) s.duracao = nova_duracao
      return Promise.resolve(s)
    }
    return fetch(`${BASE}/servicos/${id}/duracao`, { method: 'PUT', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify({ nova_duracao }) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },

  // Gestores
  getGestores: () => request<Array<any>>('/gestores'),
  createGestor: (payload: any) => {
    const body = { nome: payload.nome || payload.name, email: payload.email, telefone: payload.telefone || payload.phone, salario: payload.salario }
    if (USE_MOCK) {
      const id = mockGestores.length + 1
      const item = { id, nome: body.nome, email: body.email }
      mockGestores.push(item)
      return Promise.resolve(item)
    }
    return fetch(`${BASE}/gestor`, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(body) })
      .then(async (r) => { if (!r.ok) throw new Error(await r.text()); return r.json() })
  },

  // Agendamentos 
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
