import { useState, useEffect } from 'react'
import Modal from '../components/modal/Modal'
import ClienteForm from '../components/modal/ClienteForm'
import { api } from '../services/api'

interface Cliente {
  id: number;
  name: string;
  email: string;
  phone: string;
  preferredService: string;
}

export default function ClientesPage() {
  const [open, setOpen] = useState(false)
  const [clientes, setClientes] = useState<Cliente[]>([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  // Carregar clientes do backend
  useEffect(() => {
    loadClientes();
  }, []);

  const loadClientes = async () => {
    try {
      setLoading(true);
      const data = await api.getClients();
      setClientes(data);
    } catch (err) {
      console.error('Erro ao carregar clientes:', err);
      setError('Erro ao carregar clientes');
    } finally {
      setLoading(false);
    }
  };

  const handleSave = () => {
    setOpen(false);
    loadClientes(); // Recarregar a lista após salvar
  };

  const handleEditar = (id: number) => {
    console.log('Editar cliente:', id);
    // Implementar edição
  };

  const handleExcluir = (id: number) => {
    // Aqui você implementará a exclusão no backend
    setClientes(clientes.filter(cliente => cliente.id !== id));
  };

  if (loading) {
    return <div className="p-6">Carregando clientes...</div>;
  }

  if (error) {
    return <div className="p-6 text-red-600">{error}</div>;
  }

  return (
    <div className="p-6">
      <div className="mb-8">
        <h1 className="text-3xl font-semibold mb-2">Clientes</h1>
        <p className="text-xl text-gray-600">Gerencie a base de clientes da barbearia</p>
      </div>

      <div className="bg-white rounded-lg border border-gray-200 overflow-hidden">
        <div className="overflow-x-auto">
          <table className="min-w-full divide-y divide-gray-200">
            <thead className="bg-gray-50">
              <tr>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Nome</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Email</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Contato</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Serviço Preferido</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Ações</th>
              </tr>
            </thead>
            <tbody className="bg-white divide-y divide-gray-200">
              {clientes.map((cliente) => (
                <tr key={cliente.id} className="hover:bg-gray-50 transition-colors">
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm font-medium text-gray-900">{cliente.name}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{cliente.email}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{cliente.phone}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{cliente.preferredService}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap text-sm font-medium">
                    <button 
                      onClick={() => handleEditar(cliente.id)}
                      className="text-blue-600 hover:text-blue-900 mr-4 font-semibold"
                    >
                      Editar
                    </button>
                    <button 
                      onClick={() => handleExcluir(cliente.id)}
                      className="text-red-600 hover:text-red-900 font-semibold"
                    >
                      Excluir
                    </button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>

        <div className="border-t border-gray-200 px-6 py-4 bg-gray-50">
          <button 
            onClick={() => setOpen(true)}
            className="bg-red-600 text-white px-6 py-2 rounded-lg hover:bg-red-700 transition duration-200 font-semibold"
            aria-label="Novo Cliente"
          >
            + Novo Cliente
          </button>
        </div>
      </div>
      
      <Modal isOpen={open} onClose={() => setOpen(false)} title="Novo Cliente">
        <ClienteForm onCancel={() => setOpen(false)} onSave={handleSave} />
      </Modal>
    </div>
  );
}