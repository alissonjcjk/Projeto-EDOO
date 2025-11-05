import { useEffect, useState } from 'react'
import Modal from '../components/modal/Modal'
import ServicosForm from '../components/modal/ServicosForm'
import { api } from '../services/api'

export default function ServicosPage() {
  const [services, setServices] = useState<Array<any>>([])
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState<string | null>(null)
  const [open, setOpen] = useState(false)
  const [editing, setEditing] = useState<any | null>(null)

  const load = async () => {
    setLoading(true)
    try {
      const s = await api.getServices()
      setServices(s as any)
    } catch (err) {
      console.error(err)
      setError('Erro ao carregar serviços')
    } finally {
      setLoading(false)
    }
  }

  useEffect(() => { load() }, [])

  const handleNew = () => { setEditing(null); setOpen(true) }

  const handleEdit = (svc: any) => { setEditing(svc); setOpen(true) }

  const handleDelete = async (id: number) => {
    if (!confirm('Confirma exclusão do serviço?')) return
    try {
      await api.deleteService(id)
      setServices((cur) => cur.filter((c: any) => c.id !== id))
    } catch (err) {
      console.error(err)
      alert('Erro ao excluir serviço')
    }
  }

  const handleSave = async (payload: { name: string; price: number; duration: number }) => {
    try {
      if (editing && editing.id) {
        await api.updateService(editing.id, { name: payload.name, price: payload.price, duration: payload.duration })
      } else {
        await api.createService({ name: payload.name, price: payload.price, duration: payload.duration })
      }
      setOpen(false)
      load()
    } catch (err) {
      console.error(err)
      alert('Erro ao salvar serviço')
    }
  }

  return (
    <div className="p-6">
      <div className="mb-8 flex items-center justify-between">
        <div>
          <h1 className="text-3xl font-semibold mb-2">Serviços</h1>
          <p className="text-xl text-gray-600">Gerencie os serviços oferecidos</p>
        </div>
        <div>
          <button onClick={handleNew} className="bg-red-600 text-white px-6 py-2 rounded-lg hover:bg-red-700 transition duration-200 font-semibold">+ Novo Serviço</button>
        </div>
      </div>

      <div className="bg-white rounded-lg border border-gray-200 overflow-hidden">
        <div className="overflow-x-auto">
          <table className="min-w-full divide-y divide-gray-200">
            <thead className="bg-gray-50">
              <tr>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Nome</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Preço</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Duração (min)</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Ações</th>
              </tr>
            </thead>
            <tbody className="bg-white divide-y divide-gray-200">
              {loading ? (
                <tr><td colSpan={4} className="px-6 py-4">Carregando...</td></tr>
              ) : error ? (
                <tr><td colSpan={4} className="px-6 py-4 text-red-600">{error}</td></tr>
              ) : services.length === 0 ? (
                <tr><td colSpan={4} className="px-6 py-4">Nenhum serviço cadastrado</td></tr>
              ) : (
                services.map((s: any) => (
                  <tr key={s.id} className="hover:bg-gray-50 transition-colors">
                    <td className="px-6 py-4 whitespace-nowrap"><div className="text-sm font-medium text-gray-900">{s.name || s.nome}</div></td>
                    <td className="px-6 py-4 whitespace-nowrap"><div className="text-sm text-gray-900">R$ { (s.preco ?? s.price ?? 0).toFixed ? (s.preco ?? s.price ?? 0).toFixed(2) : String(s.preco ?? s.price ?? 0) }</div></td>
                    <td className="px-6 py-4 whitespace-nowrap"><div className="text-sm text-gray-900">{s.duracao ?? s.duration ?? s.duration_minutes ?? '-'}</div></td>
                    <td className="px-6 py-4 whitespace-nowrap text-sm font-medium">
                      <button onClick={() => handleEdit(s)} className="text-blue-600 hover:text-blue-900 mr-4 font-semibold">Editar</button>
                      <button onClick={() => handleDelete(s.id)} className="text-red-600 hover:text-red-900 font-semibold">Excluir</button>
                    </td>
                  </tr>
                ))
              )}
            </tbody>
          </table>
        </div>
      </div>

      <Modal isOpen={open} onClose={() => setOpen(false)} title={editing ? 'Editar Serviço' : 'Novo Serviço'}>
        <ServicosForm onCancel={() => setOpen(false)} onSave={handleSave} initial={editing} />
      </Modal>
    </div>
  )
}
